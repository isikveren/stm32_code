
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
		ADC_GetValue();

		// Y
		OLED_ShowNum(2, 3, AD_Value[0], 4);

		// X

		OLED_ShowNum(3, 3, AD_Value[1], 4);

		if (AD_Value[0] > 2100)
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
