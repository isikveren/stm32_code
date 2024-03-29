

#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "Serial.h"
#include "LED.h"
#include "gizwits_product.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
			;
		Delay_ms(20);
		gizwitsSetMode(WIFI_SOFTAP_MODE);
		printf("按键按下！  配网OK\r");
		// LED_Turn();
		KeyNum = 1;
	}

	return KeyNum;
}
