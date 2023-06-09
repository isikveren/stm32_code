#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "L298N.h"
#include "ds18b20.h"
#include "Serial.h"
#include "string.h"

uint8_t KeyNum;					// 按键接收
uint8_t Speed = 0;				// 风扇转速百分比
float temper;					// 接收传感器获取的温度
uint8_t temper_i, temper_f;		// 温度的整数部分和小数部分
uint8_t flag = 0, set_flag = 0; // 开关信号和阈值选择信号
uint8_t MIN = 18, MAX = 30;		// 最低阈值和最高阈值
uint8_t T[4] = {0};				// 温度区间
void System_Init()				// 系统初始化
{

	OLED_Init();	// OLED初始化
	DS18B20_Init(); // 温度传感器初始化
	Fan_Init();		// 风扇初始化
	Key_Init();		// 按键初始化
	Serial_Init();	// 串口初始化
}

void display_status(); // OLED显示子程序
void key_op();		   // 按键子程序
void serial_m();	   // 串口子程序
void fan_auto();	   // 驱动调速子程序

int main(void)
{
	System_Init();						   // 系统初始化
	Serial_SendString("begin\r\n");		   // 串口打印输出开始
	OLED_ShowString(1, 1, "Temp:   .  C"); // 屏幕预显示
	OLED_ShowString(2, 1, "fan OFF,gear:   ");
	OLED_ShowString(3, 1, "MIN   C,MAX   C");
	OLED_ShowString(4, 1, "Speed:");
	while (1)
	{
		temper = DS18B20_GetTemperture();	  // 温度的获取
		temper_i = temper;					  // 取温度整数部分
		temper_f = (int)(temper * 100) % 100; // 取温度小数部分
		serial_m();							  // 串口子程序
		key_op();							  // 按键子程序
		T[0] = MIN + (MAX - MIN) / 4;		  // 温度区间T0的设定
		T[1] = MIN + (MAX - MIN) / 2;		  // 温度区间T1的设定
		T[2] = MIN + (MAX - MIN) * 3 / 4;	  // 温度区间T2的设定
		if (flag == 1)
		{
			fan_auto(); // 有开关信号则启动风扇自动调速
		}
		display_status(); // OLED显示各种状态信息
	}
}

void display_status()
{
	OLED_ShowNum(3, 5, MIN, 2);
	OLED_ShowNum(3, 13, MAX, 2);
	OLED_ShowNum(1, 7, temper_i, 2);
	OLED_ShowNum(1, 10, temper_f, 2);
	if (set_flag % 2 == 0)
	{
		OLED_ShowString(3, 4, "*");
		OLED_ShowString(3, 12, " ");
	}
	else
	{
		OLED_ShowString(3, 4, " ");
		OLED_ShowString(3, 12, "*");
	}
	if (flag == 1)
	{
		if (Speed == 0)
		{
			OLED_ShowString(2, 14, "0  ");
			OLED_ShowString(4, 8, "  0");
		}
		if (Speed == 20)
		{
			OLED_ShowString(2, 14, "1  ");
			OLED_ShowString(4, 8, " 20");
		}
		if (Speed == 40)
		{
			OLED_ShowString(2, 14, "2  ");
			OLED_ShowString(4, 8, " 40");
		}
		if (Speed == 60)
		{
			OLED_ShowString(2, 14, "3  ");
			OLED_ShowString(4, 8, " 60");
		}
		if (Speed == 80)
		{
			OLED_ShowString(2, 14, "4  ");
			OLED_ShowString(4, 8, " 80");
		}
		if (Speed == 100)
		{
			OLED_ShowString(2, 14, "ALL");
			OLED_ShowString(4, 8, "100");
		}
		OLED_ShowString(2, 5, "ON ");
	}
	else
	{
		OLED_ShowString(2, 5, "OFF");
		OLED_ShowString(4, 8, "  0");
		OLED_ShowString(2, 14, "   ");
	}
}

void key_op() // 按键子程序
{
	KeyNum = Key_GetNum();
	if (KeyNum == 1)
	{
		flag = Fan_Turn();
	}
	if (KeyNum == 2)
	{
		set_flag = set_flag + 1;
	}
	if (KeyNum == 3)
	{
		if (set_flag % 2 == 0)
		{
			if (MIN < MAX)
			{
				MIN = MIN + 1;
			}
		}
		else
		{
			if (MAX < 100)
			{
				MAX = MAX + 1;
			}
		}
	}
	if (KeyNum == 4)
	{
		if (set_flag % 2 == 0)
		{
			if (MIN > 0)
			{
				MIN = MIN - 1;
			}
		}
		else
		{
			if (MIN < MAX)
			{
				MAX = MAX - 1;
			}
		}
	}
}
void serial_m()
{
	if (Serial_RxFlag == 1)
	{
		if (strcmp(Serial_RxPacket, "fan_turn") == 0)
		{
			flag = Fan_Turn();
		}
		else if (strcmp(Serial_RxPacket, "change") == 0)
		{
			Serial_SendString("Change success!\r\n");
			set_flag = set_flag + 1;
		}
		else if (strcmp(Serial_RxPacket, "+") == 0)
		{
			Serial_SendString("+\r\n");
			if (set_flag % 2 == 0)
			{
				if (MIN < MAX)
				{
					MIN = MIN + 1;
				}
			}
			else
			{
				if (MAX < 100)
				{
					MAX = MAX + 1;
				}
			}
		}
		else if (strcmp(Serial_RxPacket, "-") == 0)
		{
			Serial_SendString("-\r\n");
			if (set_flag % 2 == 0)
			{
				if (MIN > 0)
				{
					MIN = MIN - 1;
				}
			}
			else
			{
				if (MIN < MAX)
				{
					MAX = MAX - 1;
				}
			}
		}
		else
		{
			Serial_SendString("ERROR_COMMAND\r\n");
		}
		Serial_RxFlag = 0;
	}
}

void fan_auto() // 风扇子程序
{
	if (temper < MIN)
	{
		Speed = 0;
	}
	if (temper > MIN && temper < T[0])
	{
		Speed = 20;
	}
	if (temper > T[0] && temper < T[1])
	{
		Speed = 40;
	}
	if (temper > T[1] && temper < T[2])
	{
		Speed = 60;
	}
	if (temper > T[2] && temper < MAX)
	{
		Speed = 80;
	}
	if (temper > MAX)
	{
		Speed = 100;
	}
	Fan_SetSpeed(Speed);
}