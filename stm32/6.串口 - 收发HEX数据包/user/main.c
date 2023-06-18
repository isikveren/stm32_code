/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-13 13:20:02
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-15 23:55:20
 * @FilePath: \DMA+ADC - 多通道 - ADC连续 循环扫描\user\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

#include <string.h>
#include "LED.h"
#include "ADC.h"

uint16_t AD_Value[2];
uint8_t s[] = "hello ", RxData;
int num = 0, i, freq;
uint16_t adc_value_x, adc_value_y, voltage;
int main(void)
{
	Serial_Init();
	OLED_Init();
	LED_Init();
	//	PWM_Init();
	//	IC_Init();
	ADC_Config();
	OLED_ShowChineseString(1, 1, 0, 4);
	OLED_ShowString(2, 1, "Y:");
	OLED_ShowString(3, 1, "X:");
	Serial_TxPacket[0] = 0x01;
	Serial_TxPacket[1] = 0x02;
	Serial_TxPacket[2] = 0x03;
	Serial_TxPacket[3] = 0x04;
	Serial_SendPacket();

	while (1)
	{

		//	if (Serial_GetRxFlag() == 1)
		//		{
		OLED_ShowHexNum(4, 1, Serial_RxPacket[0], 2);
		OLED_ShowHexNum(4, 4, Serial_RxPacket[1], 2);
		OLED_ShowHexNum(4, 7, Serial_RxPacket[2], 2);
		OLED_ShowHexNum(4, 10, Serial_RxPacket[3], 2);
		//	}
		// Y
		OLED_ShowNum(2, 3, AD_Value[0], 4);

		// X

		OLED_ShowNum(3, 3, AD_Value[1], 4);
		// Serial_Printf("x:%d,Y:%d", (int)AD_Value[1],(int)AD_Value[0]);

		if (AD_Value[0] > 2200)
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			Serial_SendString("上! ");
		}
		else if (AD_Value[0] < 2000)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			Serial_SendString("下! ");
		}
		if (AD_Value[1] > 2200)
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			Serial_SendString("左! ");
		}
		else if (AD_Value[1] < 2000)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			Serial_SendString("右! ");
		}
		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
		{
			RxData = USART_ReceiveData(USART1);
			OLED_ShowHexNum(4, 1, RxData, 2);
		}
		//	Delay_ms(10);
	}
}
