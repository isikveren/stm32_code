/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-03 11:48:37
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-06 22:09:12
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
int num = 0;
int main(void)
{
	OLED_Init();
	Timer_Init();

	OLED_ShowString(2, 1, "CNT:");
	OLED_ShowChineseString(1, 1, 0, 4);
	OLED_ShowChineseString(3, 1, 0, 4);
	OLED_ShowChineseString(4, 1, 0, 4);

	while (1)
	{

		/* code */
		OLED_ShowNum(1, 10, num, 2);
		OLED_ShowNum(2, 5, TIM_GetCounter(TIM2), 8);
	}
}
