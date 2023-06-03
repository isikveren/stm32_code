#include "debug.h"
#include "system.h"
#include "LED.h"
u8 j = 1;
void System_Init()
{

    Delay_Init();
    LED_Init();
}
void System_Loop()
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_0, !GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0));
    GPIO_WriteBit(GPIOA, GPIO_Pin_1, (j == 0) ? (j = Bit_SET) : (j = Bit_RESET));
    Delay_Ms(250);
}
