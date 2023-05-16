#include <REGX52.h>
#include "MatrixKey.h"
#include "LCD1602.h"
#include "delay.h"
#include "Timer.h"
#include <intrins.h>
unsigned char KeyNum, LEDNum = 0, ledflag = 0, sw = 0;
unsigned int clock = 0, sec = 0, min = 0, hour = 0;
unsigned int Password = 0, count = 4, flag = 1;
unsigned char tmp;
int main(void)
{
    //   LCD_Init();
    //   LCD_ShowString(1, 1, "CLOCK:");
    Timer0_Init();
    P2 = 0xfe;
    tmp = P2;
    while (1)
    {
        if (sec / 60 >= 1)
        {
            min++;
            sec = 0;
        }
        KeyNum = GetKey();
        if (KeyNum == 1)
        {
            ledflag++;
        }
        if (KeyNum == 2)
        {
            sw++;
        }
    }
}

void Timer0_Routine() interrupt 1
{

    TL0 = 0x18; // 设置定时初始值
    TH0 = 0xFC; // 设置定时初始值
    clock++;

    if (clock >= 500)
    {

        sec += 1;
        //    LCD_ShowNum(1, 8, sec, 2);
        // P2_0 = ~P2_0;
        clock = 0;
        if (sw % 2 == 1)
        {
            P2 = 0xff;
        }
        else
        {
            if (ledflag % 2 == 1)
            {
                tmp = _cror_(tmp, 1);
            }
            else
            {
                tmp = _crol_(tmp, 1);
            }
            P2 = tmp;
        }
    }
}