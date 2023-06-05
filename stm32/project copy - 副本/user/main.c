/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-05 14:38:47
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-05 14:42:07
 * @FilePath: \project copy - 副本\user\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#
#include "L298N.h"
#include "ds18b20.h"
#include "Serial.h"
#include "string.h"

int main(void)
{
	OLED_Init();
	Fan_Init();
	OLED_ShowString(1, 1, "speed");
	Fan_SetSpeed(50);
	while (1)
	{
	}
}