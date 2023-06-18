/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-13 13:20:02
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-16 09:35:59
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

#include "string.h"
uint16_t AD_Value[2];
uint8_t s[] = "hello ", RxData;
int num = 0, i, freq;
uint16_t adc_value_x, adc_value_y, voltage;
int main(void)
{
	Serial_Init();
	OLED_Init();
	LED_Init();

	ADC_Config();
	//	OLED_ShowChineseString(1, 1, 0, 4);
	OLED_ShowString(1, 1, "TxPacket:");
	OLED_ShowString(3, 1, "RxPacket:");

	Serial_Printf("你好世界");
	while (1)
	{
		if (Serial_GetRxFlag() == 1)
		{
			OLED_ShowString(4, 1, "              ");
			OLED_ShowString(4, 1, Serial_RxPacket);
			if (strcmp(Serial_RxPacket, "led_on") == 0)
			{
				GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			}
			if (strcmp(Serial_RxPacket, "led_off") == 0)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_13);
			}
		}
	}
}
