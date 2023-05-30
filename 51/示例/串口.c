
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