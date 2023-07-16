/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-26 12:29:19
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-05-28 14:39:53
 * @FilePath: \project copy 2\Hardware\LED.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h" // Device header
#include "Serial.h"
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_SetBits(GPIOC, GPIO_Pin_13 );
}



void LED_ON(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	printf("LED ON\r");
}

void LED_OFF(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	printf("LED OFF\r");
}
void LED_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13) == 0)
	{
		LED_OFF();
	}
	else
	{
		LED_ON();
	}
}

