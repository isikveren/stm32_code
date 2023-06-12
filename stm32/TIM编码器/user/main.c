/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-03 11:48:37
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-09 23:38:38
 * @FilePath: \小车\user\main.c
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

int num = 0, i, freq;

void duoji(float n)
{
	PWM_SetCompare2(2000 * n / 180 + 500);
}
int main(void)
{
	OLED_Init();
	// Timer_Init();
	PWM_Init();
	IC_Init();
	OLED_ShowString(2, 1, "CNT:");
	OLED_ShowChineseString(1, 1, 0, 4);
	//	OLED_ShowChineseString(3, 1, 0, 4);
	OLED_ShowChineseString(4, 1, 4, 2);
	OLED_ShowString(4, 5, ":");
	PWM_SetPrescaler(7200 - 1); // 72M/(PSC - 1)/100
	PWM_SetCompare1(50);		// 占空比 50/100
	while (1)
	{
		// for (i = 0; i <= 180; i += 60)
		// {
		// 	duoji(i);
		// 	Delay_ms(500);
		// }
		// for (i = 180; i >= 0; i -= 30)
		// {
		// 	duoji(i);
		// 	Delay_ms(500);
		// }

		// duoji(45);
		// Delay_ms(600);
		// duoji(90);
		// Delay_ms(600);
		// duoji(45);
		// Delay_ms(600);

		freq = IC_GetFreq();
		OLED_ShowNum(1, 10, num, 2);
		OLED_ShowNum(4, 7, freq, 5);
		OLED_ShowNum(3, 7, IC_GetDuty(), 5);
		OLED_ShowNum(2, 5, TIM_GetCounter(TIM2), 8);
	}
}
