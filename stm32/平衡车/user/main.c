/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-13 13:20:02
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-18 15:21:26
 * @FilePath: \DMA+ADC - 多通道 - ADC连续 循环扫描\user\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

#include <string.h>
#include "LED.h"
#include "ADC.h"
#include "MPU6050.h"
#include "string.h"
int16_t AX, AY, AZ, GX, GY, GZ;
int main(void)
{
	OLED_Init();
	//	MPU6050_Init();
	//
	//	OLED_ShowString(1, 1, "ID:");
	//	ID = MPU6050_GetID();
	//	OLED_ShowHexNum(1, 4, ID, 2);
	//
	MPU6050_Init();

	OLED_ShowHexNum(1, 1, MPU6050_GetID(), 2);
	OLED_ShowString(2, 1, "x");
	OLED_ShowString(3, 1, "y");
	OLED_ShowString(4, 1, "z");

	while (1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(2, 3, AX, 5);
		OLED_ShowSignedNum(3, 3, AY, 5);
		OLED_ShowSignedNum(4, 3, AZ, 5);
		OLED_ShowSignedNum(2, 11, GX, 5);
		OLED_ShowSignedNum(3, 11, GY, 5);
		OLED_ShowSignedNum(4, 11, GZ, 5);
	}
}
