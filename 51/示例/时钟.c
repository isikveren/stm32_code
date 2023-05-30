/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-15 10:40:55
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-05-30 19:55:18
 * @FilePath: \51\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: isikveren lauxunzi@outlookom
 * @Date: 2023-05-15 10:40:55
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-05-30 18:45:17
 * @FilePath: \project copy 2d:\stm32_code\51\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <REGX52.h>
#include "delay.h"
#include "Timer.h"
#include "LCD1602.h"
#include "DS1302.h"
#include "key.h"

unsigned char keynum, clock;
int main(void)
{
    LCD_Init();
    DS1302_Init();
    DS1302_SetTime();
    LCD_ShowString(1, 1, "RTC");
    LCD_ShowString(1, 7, "20");
    LCD_ShowString(1, 9, "  -  -");
    LCD_ShowString(2, 9, "  :  :");
    while (1)
    {
        keynum = Key();
        if (keynum)
        {
            LCD_ShowNum(1, 1, keynum, 2);
            P2 = keynum;
        }
        DS1302_ReadTime();

        LCD_ShowNum(1, 9, DS1302_Time[0], 2);
        LCD_ShowNum(1, 12, DS1302_Time[1], 2);
        LCD_ShowNum(1, 15, DS1302_Time[2], 2);
        LCD_ShowNum(2, 9, DS1302_Time[3], 2);
        LCD_ShowNum(2, 12, DS1302_Time[4], 2);
        LCD_ShowNum(2, 15, DS1302_Time[5], 2);
    }
}

void Timer0_Routine() interrupt 1
{

    TL0 = 0x18; // 设置定时初始值
    TH0 = 0xFC; // 设置定时初始值
    clock++;

    if (clock >= 1000)
    {

        //    LCD_ShowNum(1, 8, sec, 2);
        // P2_0 = ~P2_0;
        clock = 0;
    }
}