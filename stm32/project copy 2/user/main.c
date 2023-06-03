#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "L298N.h"
#include "ds18b20.h"
#include "Serial.h"
#include "string.h"

uint8_t KeyNum;	   // 按键接收
uint8_t Speed = 0; // 风扇转速百分比

uint8_t flag = 0, set_flag = 0, count = 0; // 开关信号和阈值选择信号
uint8_t MIN = 18, MAX = 30;				   // 最低阈值和最高阈值
uint8_t T[4] = {0};						   // 温度区间
void System_Init()						   // 系统初始化
{

	OLED_Init();	// OLED初始化
	DS18B20_Init(); // 温度传感器初始化
	Fan_Init();		// 风扇初始化
	Key_Init();		// 按键初始化
	Serial_Init();	// 串口初始化
}

void key_op(); // 按键子程序

int main(void)
{
	System_Init(); // 系统初始化

	OLED_ShowString(1, 1, "Speed:");

	while (1)
	{
		Speed = 50 * count;
		key_op(); // 按键子程序
		Fan_SetSpeed(Speed);
		OLED_ShowNum(1, 7, Speed, 3);
		OLED_ShowNum(2, 7, flag, 3);
	}
}

void key_op() // 按键子程序
{
	KeyNum = Key_GetNum();
	if (KeyNum == 1)
	{
		count++;
		if (count > 2)
		{
			count = 0;
		}
	}
	if (KeyNum == 2)
	{
		flag = Fan_Turn();
	}
}
