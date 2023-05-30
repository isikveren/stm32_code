/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-15 10:40:55
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-05-30 11:01:02
 * @FilePath: \project copy 2d:\stm32_code\51\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <REGX52.h>
#include "delay.h"
// #include "UART.h"
unsigned char led[] = {

    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x08,
    0x30,
    0xCF,
    0x00,
    0x64,
    0xC8,
    0x41,
    0x5F,
    0x40,
    0x48,
    0x64,
    0x00,
    0x10,
    0x18,
    0x35,
    0xD6,
    0x19,
    0x00,
    0x10,
    0x92,
    0x91,
    0xBF,
    0xD0,
    0x10,
    0x10,
    0x00,
    0x00,
    0x7A,
    0x00,
    0x00,
    0x00,
    0x00,

    0x00,
    0x00,
    0x00,
    0x00,
};
sbit SCK = P3 ^ 6; // RCLK
sbit RCK = P3 ^ 5; // SRCLK
sbit SER = P3 ^ 4; // SER

void _74HC595_WriteByte(unsigned char Byte)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        SER = Byte & (0x80 >> i); // 1000 0000
        SCK = 1;
        SCK = 0;
    }
    RCK = 1;
    RCK = 0;
}
void MatrixLED_ShowColumn(unsigned char Column, Data)
{
    _74HC595_WriteByte(Data);
    P0 = ~(0x80 >> Column);
    Delay(1);
    P0 = 0xff;
}
int main(void)
{
    unsigned char i, j = 0, count = 0;
    RCK = 0;
    SCK = 0;
    while (1)
    {

        for (i = 0; i < 8; i++)
        {
            MatrixLED_ShowColumn(i, led[count + i]);
        }
        j++;
        if (j > 10)
        {
            count++;
            j = 0;
            if (count > 36)
            {
                count = 0;
            }
        }
    }
}