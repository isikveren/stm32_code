/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-15 10:40:55
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-05-31 11:09:34
 * @FilePath: \51\main.c
 * @Description: DS1302时钟，
 */

#include <REGX52.h>
#include "delay.h"
#include "Timer.h"
#include "LCD1602.h"
#include "DS1302.h"
#include "key.h"

unsigned char keynum, mode, timeSetSelect = 0, timesetflag = 0;
void showtime(void);
void settime(void);
int main(void)
{
    LCD_Init();
    Timer0_Init();
    DS1302_Init();
    DS1302_SetTime();
    LCD_ShowString(1, 1, "RTC");
    LCD_ShowString(1, 7, "20");
    LCD_ShowString(1, 9, "  -  -");
    LCD_ShowString(2, 9, "  :  :");
    while (1)
    {
        keynum = Key();
        // if (keynum)
        // {
        //     LCD_ShowNum(2, 1, keynum, 2);
        // }

        if (keynum == 1)
        {
            if (mode == 0)
            {
                mode = 1;
            }
            else
            {
                mode = 0;
                DS1302_SetTime();
            }
        }
        switch (mode)
        {
        case 0:
            showtime();
            break;
        case 1:
            settime();
            break;
        }
    }
}

void showtime(void)
{
    DS1302_ReadTime();

    LCD_ShowNum(1, 9, DS1302_Time[0], 2);
    LCD_ShowNum(1, 12, DS1302_Time[1], 2);
    LCD_ShowNum(1, 15, DS1302_Time[2], 2);
    LCD_ShowNum(2, 9, DS1302_Time[3], 2);
    LCD_ShowNum(2, 12, DS1302_Time[4], 2);
    LCD_ShowNum(2, 15, DS1302_Time[5], 2);
}

void settime(void)
{
    if (keynum == 2)
    {
        timeSetSelect = timeSetSelect + 1;
        timeSetSelect %= 6;
    }
    if (keynum == 3)
    {
        DS1302_Time[timeSetSelect]++;
        if (DS1302_Time[0] > 99)
        {
            DS1302_Time[0] = 0;
        }
        if (DS1302_Time[1] > 12)
        {
            DS1302_Time[1] = 1;
        }
        if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time[1] == 10 || DS1302_Time[1] == 12)
        {
            if (DS1302_Time[2] < 0)
            {
                DS1302_Time[2] = 31;
            }
            if (DS1302_Time[2] > 31)
            {
                DS1302_Time[2] = 1;
            }
        }
        else if (DS1302_Time[1] == 2)
        {
            if (DS1302_Time[0] % 4 == 0)
            {
                if (DS1302_Time[2] < 1)
                {
                    DS1302_Time[2] = 29;
                }
                if (DS1302_Time[2] > 29)
                {
                    DS1302_Time[2] = 1;
                }
            }
            else
            {
                if (DS1302_Time[2] < 1)
                {
                    DS1302_Time[2] = 28;
                }
                if (DS1302_Time[2] > 28)
                {
                    DS1302_Time[2] = 1;
                }
            }
        }
        else
        {
            if (DS1302_Time[2] < 1)
            {
                DS1302_Time[2] = 30;
            }
            if (DS1302_Time[2] > 30)
            {
                DS1302_Time[2] = 1;
            }
        }

        if (DS1302_Time[3] > 23)
        {
            DS1302_Time[3] = 0;
        }
        if (DS1302_Time[4] > 59)
        {
            DS1302_Time[4] = 0;
        }
        if (DS1302_Time[5] > 59)
        {
            DS1302_Time[5] = 0;
        }
    }
    if (keynum == 4)
    {
        DS1302_Time[timeSetSelect]--;

        if (DS1302_Time[0] < 0)
        {
            DS1302_Time[0] = 99;
        }
        if (DS1302_Time[1] < 1)
        {
            DS1302_Time[1] = 12;
        }
        if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time[1] == 10 || DS1302_Time[1] == 12)
        {
            if (DS1302_Time[2] < 0)
            {
                DS1302_Time[2] = 31;
            }
            if (DS1302_Time[2] > 31)
            {
                DS1302_Time[2] = 1;
            }
        }
        else if (DS1302_Time[1] == 2)
        {
            if (DS1302_Time[0] % 4 == 0)
            {
                if (DS1302_Time[2] < 1)
                {
                    DS1302_Time[2] = 29;
                }
                if (DS1302_Time[2] > 29)
                {
                    DS1302_Time[2] = 1;
                }
            }
            else
            {
                if (DS1302_Time[2] < 1)
                {
                    DS1302_Time[2] = 28;
                }
                if (DS1302_Time[2] > 28)
                {
                    DS1302_Time[2] = 1;
                }
            }
        }
        else
        {
            if (DS1302_Time[2] < 1)
            {
                DS1302_Time[2] = 30;
            }
            if (DS1302_Time[2] > 30)
            {
                DS1302_Time[2] = 1;
            }
        }

        if (DS1302_Time[3] < 0)
        {
            DS1302_Time[3] = 23;
        }
        if (DS1302_Time[4] < 0)
        {
            DS1302_Time[4] = 59;
        }
        if (DS1302_Time[5] < 0)
        {
            DS1302_Time[5] = 59;
        }
    }
    if (timesetflag == 1 && timeSetSelect == 0)
    {
        LCD_ShowString(1, 9, "  ");
    }
    else
    {
        LCD_ShowNum(1, 9, DS1302_Time[0], 2);
    }
    if (timesetflag == 1 && timeSetSelect == 1)
    {
        LCD_ShowString(1, 12, "  ");
    }
    else
    {
        LCD_ShowNum(1, 12, DS1302_Time[1], 2);
    }
    if (timesetflag == 1 && timeSetSelect == 2)
    {
        LCD_ShowString(1, 15, "  ");
    }
    else
    {
        LCD_ShowNum(1, 15, DS1302_Time[2], 2);
    }
    if (timesetflag == 1 && timeSetSelect == 3)
    {
        LCD_ShowString(2, 9, "  ");
    }
    else
    {
        LCD_ShowNum(2, 9, DS1302_Time[3], 2);
    }
    if (timesetflag == 1 && timeSetSelect == 4)
    {
        LCD_ShowString(2, 12, "  ");
    }
    else
    {
        LCD_ShowNum(2, 12, DS1302_Time[4], 2);
    }
    if (timesetflag == 1 && timeSetSelect == 5)
    {
        LCD_ShowString(2, 15, "  ");
    }
    else
    {
        LCD_ShowNum(2, 15, DS1302_Time[5], 2);
    }

    // LCD_ShowNum(2, 4, timeSetSelect, 2);
    // LCD_ShowNum(2, 7, timesetflag, 2);

    // LCD_ShowNum(1, 12, DS1302_Time[1], 2);
    // LCD_ShowNum(1, 15, DS1302_Time[2], 2);
    // LCD_ShowNum(2, 9, DS1302_Time[3], 2);
    // LCD_ShowNum(2, 12, DS1302_Time[4], 2);
    // LCD_ShowNum(2, 15, DS1302_Time[5], 2);
}

void Timer0_Routine() interrupt 1
{
    static unsigned int clock;
    TL0 = 0x18; // 设置定时初始值
    TH0 = 0xFC; // 设置定时初始值
    clock++;

    if (clock >= 500)
    {

        clock = 0;
        timesetflag = !timesetflag;
    }
}