#include "ch32f10x.h"
#include "OLED.h"

uint8_t KeyNum;					// 按键接收
uint8_t Speed = 0;				// 风扇转速百分比
float temper;					// 接收传感器获取的温度
uint8_t temper_i, temper_f;		// 温度的整数部分和小数部分
uint8_t flag = 1, set_flag = 0; // 开关信号和阈值选择信号
uint8_t MIN = 18, MAX = 30;		// 最低阈值和最高阈值
uint8_t T[4] = {0};				// 温度区间
void display_status();
int main()
{
	OLED_Init();
	OLED_ShowString(1, 1, "Temp:   .  C");
	OLED_ShowString(2, 1, "fan OFF,gear:   ");
	OLED_ShowString(3, 1, "MIN   C,MAX   C");
	OLED_ShowString(4, 1, "Speed:");
	while (1)
	{

		display_status();
	}
}

void display_status() // OLED显示子程序
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
}