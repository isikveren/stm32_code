/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-16 15:15:20
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-05-30 19:32:11
 * @FilePath: \51\Timer.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <REGX52.h>

void Timer0_Init(void) // 1毫秒@12.000MHz
{
    TMOD &= 0xF0; // 设置定时器模式
    TMOD |= 0x01; // 设置定时器模式
    TL0 = 0x18;   // 设置定时初始值
    TH0 = 0xFC;   // 设置定时初始值
    TF0 = 0;      // 清除TF0标志
    TR0 = 1;      // 定时器0开始计时
    ET0 = 1;
    EA = 1;
    PT0 = 0;
}