
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
uint16_t adc_value, voltage;
int main(void)
{
	OLED_Init();
	LED_Init();
	//	PWM_Init();
	//	IC_Init();
	ADC_Config();
	OLED_ShowChineseString(1, 1, 0, 4);
	OLED_ShowString(2, 1, "Y:");
	while (1)
	{
		adc_value_y = ADC_GetValue();
		voltage = adc_value * 3300 / 4095;
		OLED_ShowNum(2, 3, adc_value, 4);
		OLED_ShowNum(2, 8, voltage / 1000, 1);
		OLED_ShowString(2, 9, ".");
		OLED_ShowNum(2, 10, (voltage % 1000) / 10, 2);
		if (adc_value > 2100)
		{
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		}
		else
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
		}

		Delay_ms(10);
		// GPIO_ResetBits(GPIOC, GPIO_Pin_13); // 将PC13引脚输出电平设置为低，点亮LED灯
		// Delay_ms(1000);						// 延时1000毫秒
		// GPIO_SetBits(GPIOC, GPIO_Pin_13);	// 将PC13引脚输出电平设置为高，熄灭LED灯
		// Delay_ms(1000);
	}
}

// void EXTI2_IRQHandler(void)
// {
// 	if (EXTI_GetITStatus(EXTI_Line2) != RESET)
// 	{
// 		num++;
// 		EXTI_ClearITPendingBit(EXTI_Line0);
// 	}
// }
