/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-25 18:46:13
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-01 22:42:45
 * @FilePath: \ch32\USER\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "ch32f10x.h"
#include "LED.h"
#include "OLED.h"

// static u16 p_ms = 0;

int main()
{
	char i;
	LED_Init();
	OLED_Init();
	OLED_ShowString(1, 1, "liuxunzi");

	OLED_ShowChineseString(1, 5, 0, 3);

	OLED_ShowChineseString(2, 1, 3, 5);
	OLED_ShowChineseString(3, 1, 8, 5);
	while (1)

	{
	}
}
