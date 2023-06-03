/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-26 12:29:20
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-05-29 12:55:52
 * @FilePath: \isikveren.github.iod:\stm32_code\按键控制速度\user\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "L298N.h"
#include "ds18b20.h"
#include "Serial.h"
#include "string.h"
unsigned char key;

void System_Init() // 系统初始化
{

	OLED_Init();	// OLED初始化
	DS18B20_Init(); // 温度传感器初始化
	Fan_Init();		// 风扇初始化
	Key_Init();		// 按键初始化
	Serial_Init();	// 串口初始化
}

int main(void)
{
	System_Init();
	while (1)
	{
		key = Key_GetNum();
		if (key == 1)
		{
		}
	}
}
