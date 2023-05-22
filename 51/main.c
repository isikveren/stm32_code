/**
 * @FilePath     : /stm32_code/51/main.c
 * @Description  :
 * @Author       : isikveren lauxunzi@outlook.com
 * @Version      : 0.0.1
 * @LastEditors  : isikveren lauxunzi@outlook.com
 * @LastEditTime : 2023-05-22 20:36:58
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2023.
 **/

#include <REGX52.h>
#include "delay.h"
#include "UART.h"
// 串口通信
unsigned char num = 0x00;

int main(void)
{
    UART_Init();
//    UART_SendByte(0x11);
    while (1)
    {
      //  UART_SendByte(num++);
     //   Delay(1000);
    }
}
void UART_Routine() interrupt 4
{
    if (RI == 1)
    {
        P2 = ~SBUF;
			UART_SendByte(SBUF);
        RI = 0;
    }
}