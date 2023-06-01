#include <REGX52.h>
#include "key.h"
#include "LCD1602.h"
#include "delay.h"
#include "Timer.h"
#include <intrins.h>
unsigned char KeyNum, LEDNum = 0, ledflag = 0, sw = 0;

unsigned char tmp;

sbit buzzer = P2 ^ 5;
void Buzzer_time(int n, int m)
{
    int M = 100000 * m / n;
    M = M / 8;
    while (M--)
    {
        buzzer = ~buzzer;
        Delay10us(n);
    }
}
int main(void)
{
    //   LCD_Init();
    //   LCD_ShowString(1, 1, "CLOCK:");
    Timer0_Init();
    P2 = 0xfe;
    tmp = P2;
    while (1)
    {
        KeyNum = Key();
        if (KeyNum == 1)
        {
            Buzzer_time(191, 1);
        }
				 if (KeyNum == 2)
        {
            Buzzer_time(170, 1);
        }
				 if (KeyNum == 3)
        {
            Buzzer_time(151, 1);
        }
				
    }
}

void Timer0_Routine() interrupt 1
{
    static unsigned int clock;
    TL0 = 0x18; // 设置定时初始值
    TH0 = 0xFC; // 设置定时初始值
    clock++;

    if (clock >= 500)
    {

        //    LCD_ShowNum(1, 8, sec, 2);
        // P2_0 = ~P2_0;
        clock = 0;
    }
}