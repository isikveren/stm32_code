#include "stm32f10x.h" // Device header
#include "PWM.h"

void Fan_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	PWM_Init();
}
void Fan_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); // 拉低引脚输出电平
}

void Fan_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1); // 拉高引脚输出电平
}
uint8_t Fan_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		return 0;
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		return 1;
	}
}
void Fan_SetSpeed(int8_t Speed)
{
	PWM_SetCompare2(Speed);
}
