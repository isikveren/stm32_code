
/**
 * @FilePath     : /stm32_code/51/UART.c
 * @Description  :
 * @Author       : isikveren lauxunzi@outlook.com
 * @Version      : 0.0.1
 * @LastEditors  : isikveren lauxunzi@outlook.com
 * @LastEditTime : 2023-05-23 19:47:32
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2023.
 **/

#include <REGX52.h>

/**
 * @brief        : 串口初始化，4800bps@12.000MHz
 * @retval       :无
 **/
void UART_Init() // 4800bps@12.000MHz
{
    SCON = 0x50; // Serial Control
    PCON |= 0x80;
    TMOD &= 0x0f;
    TMOD |= 0x20; // 设置定时器模式
    TL1 = 0xF3;   // 设置定时初始值
    TH1 = 0xF3;   // 设置定时初始值
    ET1 = 0;      // 禁止定时器中断
    TR1 = 1;      // 定时器1开始计时
    EA = 1;
    ES = 1;
}

/**
 * @brief        : 串口发送一个字节数据
 * @param         {unsigned char} Byte:要发送的一个字节数据
 * @retval       :无
 **/

void UART_SendByte(unsigned char Byte)
{
    SBUF = Byte;
    while (TI == 0) // TI不为0时结束
        ;
    TI = 0; // TI复位
}