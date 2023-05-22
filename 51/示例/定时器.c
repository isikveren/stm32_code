#include <REGX52.h>
#include "LCD1602.h"
#include "delay.h"
#include "Timer.h"

unsigned int clock = 0, sec = 56, min = 59, hour = 23;

int main(void)
{
    LCD_Init();
    LCD_ShowString(1, 1, "CLOCK:");
    LCD_ShowString(2, 1, "  :  :");
    Timer0_Init();

    while (1)
    {
        LCD_ShowNum(2, 1, hour, 2);
        LCD_ShowNum(2, 4, min, 2);
        LCD_ShowNum(2, 7, sec, 2);
    }
}

void Timer0_Routine() interrupt 1
{

    TL0 = 0x18; // 设置定时初始值
    TH0 = 0xFC; // 设置定时初始值
    clock++;

    if (clock >= 1000)
    {

        sec += 1;
        if (sec >= 60)
        {
            min++;
            if (min >= 60)
            {
                hour++;
                if (hour >= 24)
                {
                    hour = 0;
                }
                min = 0;
            }
            sec = 0;
        }
        //    LCD_ShowNum(1, 8, sec, 2);
        // P2_0 = ~P2_0;
        clock = 0;
    }
}