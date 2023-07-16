/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-18 15:27:18
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-07-15 00:01:29
 * @FilePath: \平衡车\user\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "ch32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include <string.h>
#include "LED.h"
#include "ds18b20.h"
// #include "Timer.h"
#include <math.h>
#include "gizwits_product.h"

float temp;
int t;

int main(void)
{
	OLED_Init();

	
//	LED_Init();
//	DS18B20_Init();
//	Serial_Init();
//	LED_turn();
//	Timer_Init();
	while (1)
	{
		OLED_ShowString(1, 1, "Temperture");
//		temp = DS18B20_GetTemperture();
//		t = (int)(temp * 10) % 10;
//		OLED_ShowString(1, 1, "Temperture");
//		OLED_ShowNum(2, 1, temp, 2);
//		OLED_ShowString(2, 3, ".");
//		OLED_ShowNum(2, 4, t, 1);
//		Serial_Printf("temp:%.1f\n", temp);
	}
}




//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//	{

//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//		gizTimerMs();
//		
//		
//		temp = DS18B20_GetTemperture();
//		t = (int)(temp * 10) % 10;
//		OLED_ShowString(1, 1, "Temperture");
//		OLED_ShowNum(2, 1, temp, 2);
//		OLED_ShowString(2, 3, ".");
//		OLED_ShowNum(2, 4, t, 1);
//		Serial_Printf("temp:%.1f\n", temp);
//	}
//}

