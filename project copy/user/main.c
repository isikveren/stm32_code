#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "L298N.h"
#include "ds18b20.h"
#include "Serial.h"
#include "string.h"

void System_Init();

uint8_t KeyNum;
uint8_t Speed = 0;
uint8_t temper_i, temper_f;
uint8_t flag = 1, set_flag = 0;
float temper;
uint8_t MIN = 18, MAX = 30;
uint8_t T[4] = {0};
int main(void)
{
	System_Init(); // 系统初始化

	OLED_ShowString(1, 1, "Temp:   .  C");
	OLED_ShowString(2, 1, "fan OFF,gear:   ");
	OLED_ShowString(3, 1, "MIN   C,MAX   C");
	OLED_ShowString(4, 1, "Speed:");

	// Serial
	Serial_Init();
	uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
	Serial_SendArray(MyArray, 4);
	Serial_SendString("begin\r\n");
	while (1)
	{
		temper = DS18B20_GetTemperture();
		temper_i = temper;
		temper_f = (int)(temper * 100) % 100;
	//	KeyNum = Key_GetNum();
		OLED_ShowNum(3, 5, MIN, 2);
		OLED_ShowNum(3, 13, MAX, 2);
		T[0] = MIN + (MAX - MIN) / 4;
		T[1] = MIN + (MAX - MIN) / 2;
		T[2] = MIN + (MAX - MIN) * 3 / 4;
		if (Serial_RxFlag == 1)
		{
			if (strcmp(Serial_RxPacket, "fan_turn") == 0)
			{

				flag = Fan_Turn();
				if (flag == 0)
				{

					OLED_ShowString(2, 5, "ON ");
					Serial_SendString("ON\r\n");
				}
				if (flag == 1)
				{

					Serial_SendString("OFF\r\n");
					OLED_ShowString(2, 5, "OFF");
					OLED_ShowString(4, 8, "  0");
						OLED_ShowString(2, 14, "   ");
				}
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
				//	OLED_ShowString(2, 1, "                ");
				//	OLED_ShowString(2, 1, "ERROR_COMMAND");
			}

			Serial_RxFlag = 0;
		}

		if (KeyNum == 1)
		{
			flag = Fan_Turn();

			if (flag == 0)
			{

				OLED_ShowString(2, 5, "ON ");
			}
			if (flag == 1)
			{

				OLED_ShowString(2, 5, "OFF");
				OLED_ShowString(4, 8, "  0");
				OLED_ShowString(2, 14, "   ");
			}
		}
		if (KeyNum == 2)
		{
			
			set_flag = set_flag + 1;
		}

		if (flag == 0)
		{

			if (temper < MIN)
			{
				Speed = 0;
				OLED_ShowString(2, 14, "0  ");
				OLED_ShowString(4, 8, "  0");
			}
			if (temper > MIN && temper < T[0])
			{
				Speed = 20;
				OLED_ShowString(2, 14, "1  ");
				OLED_ShowString(4, 8, " 20");
			}
			if (temper > T[0] && temper < T[1])
			{
				Speed = 40;
				OLED_ShowString(2, 14, "2  ");
				OLED_ShowString(4, 8, " 40");
			}
			if (temper > T[1] && temper < T[2])
			{
				Speed = 60;
				OLED_ShowString(2, 14, "3  ");
				OLED_ShowString(4, 8, " 60");
			}
			if (temper > T[2] && temper < MAX)
			{
				Speed = 80;
				OLED_ShowString(2, 14, "4  ");
				OLED_ShowString(4, 8, " 80");
			}
			if (temper > MAX)
			{
				Speed = 100;
				OLED_ShowString(2, 14, "ALL");
				OLED_ShowString(4, 8, "100");
			}

			Fan_SetSpeed(Speed);
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
	}
}

void System_Init()
{

	OLED_Init();
	DS18B20_Init();
	Fan_Init();
	Key_Init();
}