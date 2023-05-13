#include "stm32f103c8t6.h"

int main(void)
{

    // unsigned int *pReg;
    // // 使能GPIOB的时钟
    // pReg = (unsigned int *)(0x40021000 + 0x18);
    RCC->APB2ENR |= (1 << 2);
#if 0
    // 设置输出模式
    // pReg = (unsigned int *)0x40010C00;
    // *pReg |= ((1) << (4 * 0));
    GPIOB_CRL &= ~((0x0f) << (4 * 0)); // 清零
    GPIOB_CRL |= ((1) << (4 * 0));
    // 控制ODR寄存器
    // pReg = (unsigned int *)0x40010C0C;

    //  *pReg &= ~(1 << 0);

    GPIOB_ODR &= ~(1 << 0);
#elif 1
    GPIOA->CRL &= ~((0x0f) << (4 * 0));
    GPIOA->CRL |= ((1) << (4 * 0));
    GPIOA->ODR &= ~(1 << 0);
#endif
    while (1)
    {

        GPIOA->ODR |= (1 << 0);

        delay(3000000);
        GPIOA->ODR &= ~(1 << 0);
        delay(3000000);
    }
}