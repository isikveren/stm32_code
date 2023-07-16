/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-26 12:29:20
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-07-15 10:09:14
 * @FilePath: \isikveren.github.iod:\stm32_code\按键控制速度\user\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"
#include "LED.h"
#include "L298N.h"
#include "ds18b20.h"
#include "Serial.h"
#include "string.h"
#include "gizwits_product.h"

float temp = 0.0f;
dataPoint_t currentDataPoint;
extern uint8_t wifi_flag;
void userHandle(void)
{
	if (wifi_flag == 1)
	{
		temp = DS18B20_GetTemperture();
		//	printf("温度：%.2f\r", temp);
		currentDataPoint.valuetemp = temp ;
	}
}
void GZ_Init(void)
{
	memset((uint8_t *)&currentDataPoint, 0, sizeof(dataPoint_t));
	gizwitsInit();
}
int main(void)
{
	DS18B20_Init(); // 温度传感器初始化
	LED_Init();
	Key_Init();	   // 按键初始化
	Serial_Init(); // 串口初始化
	GZ_Init();
	printf("初始化成功!\r");

	temp = DS18B20_GetTemperture();
	printf("温度：%.2f\r", temp);
	while (1)
	{
		Key_GetNum();
		userHandle();
		gizwitsHandle((dataPoint_t *)&currentDataPoint);
	
	}
}
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		gizTimerMs();
	}
}

