
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
		adc_value_y = ADC_GetValue(ADC_Channel_0);
		adc_value_x = ADC_GetValue(ADC_Channel_1);
		voltage = adc_value_y * 3300 / 4095;
		// Y
		OLED_ShowNum(2, 3, adc_value_y, 4);
		OLED_ShowNum(2, 8, voltage / 1000, 1);
		OLED_ShowString(2, 9, ".");
		OLED_ShowNum(2, 10, (voltage % 1000) / 10, 2);
		// X
		voltage = adc_value_x * 3300 / 4095;
		OLED_ShowNum(3, 3, adc_value_x, 4);
		OLED_ShowNum(3, 8, voltage / 1000, 1);
		OLED_ShowString(3, 9, ".");
		OLED_ShowNum(3, 10, (voltage % 1000) / 10, 2);
		if (adc_value_x > 2100)
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
