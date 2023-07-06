#include "stm32f10x.h" // Device header

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // 使能GPIOC时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		  // PC13引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 输出速率50MHz

	GPIO_Init(GPIOC, &GPIO_InitStructure); // 初始化PC13引脚
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}
