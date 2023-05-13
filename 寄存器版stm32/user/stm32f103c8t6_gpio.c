#include "stm32f103c8t6_gpio.h"

void GPIO_SetBits_2(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BSRR |= GPIO_Pin;
}

void GPIO_ResetBits_2(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BRR |= GPIO_Pin;
}
