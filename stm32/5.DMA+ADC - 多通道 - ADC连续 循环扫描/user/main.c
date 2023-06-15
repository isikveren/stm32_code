/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-13 13:20:02
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-13 13:34:26
 * @FilePath: \DMA+ADC - 多通道 - ADC连续 循环扫描\user\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "key.h"
#include "ultrasonic.h"
#include "Buzzer.h"
#include "Timer.h"
#include "IC.h"
#include "LED.h"
#include "ADC.h"
uint16_t AD_Value[2];
int num = 0, i, freq;
uint16_t adc_value_x, adc_value_y, voltage;
int main(void)
{
	OLED_Init();
	LED_Init();
	//	PWM_Init();
	//	IC_Init();
	ADC_Config();
	OLED_ShowChineseString(1, 1, 0, 4);
	OLED_ShowString(2, 1, "Y:");
	OLED_ShowString(3, 1, "X:");
	while (1)
	{

		// Y
		OLED_ShowNum(2, 3, AD_Value[0], 4);

		// X

		OLED_ShowNum(3, 3, AD_Value[1], 4);

		if (AD_Value[0] > 2200)
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		}
		else
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
		}

		Delay_ms(10);
	}
}
