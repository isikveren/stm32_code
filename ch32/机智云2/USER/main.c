/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-25 18:46:13
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-23 12:12:28
 * @FilePath: \ch32\USER\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "ch32f10x.h"
#include "LED.h"
#include "OLED.h"
#include "ds18b20.h"
#include "Delay.h"
#include "Timer.h"
#include "serial.h" 
#include "gizwits_product.h"

#include "key.h"
float temp;
uint8_t tem =0,key=0;
int count =0;
int main()
{

	LED_Init();
	OLED_Init();
	DS18B20_Init();
//	usart3_init();
//	Key_Init();
	OLED_ShowChineseString(1, 1, 13, 4);
//	Timer_Init();
	while (1)
	{
		Key_GetNum();
	
		temp = DS18B20_GetTemperture();
		tem = (uint8_t)(temp*10)%10;
		OLED_ShowNum(2, 1, temp, 2);
		OLED_ShowNum(2, 4, tem, 1);
		OLED_ShowNum(3, 1, count, 6);
	}
}
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{

		gizTimerMs();
		count++;
		if(count>10000)	count=0;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
