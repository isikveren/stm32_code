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
#include "TFT.h"
#include "Delay.h"
#include "bmp.h"
// static u16 p_ms = 0;
uint8_t i = 0;
u8 ref = 0;					// 刷新显示
u16 vx = 15542, vy = 11165; // 比例因子，此值除以1000之后表示多少个AD值代表一个像素点
u16 chx = 140, chy = 146;	// 默认像素点坐标为0时的AD起始值
void xianshi()				// 显示信息
{
	u16 lx, ly;
	BACK_COLOR = WHITE;
	POINT_COLOR = BLACK;
	showhanzi(0 * 32 + 1, 0, 0);
	showhanzi(1 * 32 + 1, 0, 1);
	showhanzi(2 * 32 + 1, 0, 2);

	// LCD_ShowString(10, 35, "1.3 IPS-SPI 240*240");
	// LCD_ShowString(10, 55, "LCD_W:");
	// LCD_ShowNum(70, 55, LCD_W, 3);
	// LCD_ShowString(110, 55, "LCD_H:");
	// LCD_ShowNum(160, 55, LCD_H, 3);
	lx = 10;
	ly = 75;
}

void showimage() // 显示40*40图片
{
	int i, j, k;

 
	for (k = 2; k < 6; k++)
	{
		for (j = 0; j < 6; j++)
		{
			Address_set(40 * j, 40 * k, 40 * j + 39, 40 * k + 39); // 坐标设置
			for (i = 0; i < 1600; i++)
			{

				LCD_WR_DATA8(image[i * 2 + 1]);
				LCD_WR_DATA8(image[i * 2]);
			}
		}
	}
	ref = 0;
}

int main()
{

	LED_Init();

	OLED_Init();
	Lcd_Init();

	LCD_Clear(WHITE); // 清屏
	BACK_COLOR = BLACK;
	POINT_COLOR = WHITE;

	xianshi(); // 显示信息
			   //	showimage(); // 显示40*40图片

	OLED_ShowString(1, 1, "liuxunzi");

	OLED_ShowChineseString(1, 5, 0, 3);

	OLED_ShowChineseString(2, 1, 3, 5);
	OLED_ShowChineseString(3, 1, 8, 5);
	OLED_ShowChineseString(4, 1, 13, 4);
	//	OLED_ShowChineseString(4, 5, 17, 4);
	showimage();

	while (1)

	{

		LCD_ShowNum(160, 0, i, 1);

		if (i == 0)
		{
			i = 7;
		}
		else
		{
			i = 0;
		}

		showhanzi(0 * 32 + 1, 33, 3 + i);
		showhanzi(1 * 32 + 1, 33, 4 + i);
		showhanzi(2 * 32 + 1, 33, 5 + i);
		showhanzi(3 * 32 + 1, 33, 6 + i);
		showhanzi(4 * 32 + 1, 33, 7 + i);
		showhanzi(5 * 32 + 1, 33, 8 + i);
		showhanzi(6 * 32 + 1, 33, 9 + i);
		//		LED0_Turn();
		Delay_ms(1000);
	}
}
