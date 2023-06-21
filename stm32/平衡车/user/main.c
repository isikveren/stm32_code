/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-18 15:27:18
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-21 21:52:02
 * @FilePath: \平衡车\user\main.c
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
// #include "Timer.h"
#include "motor.h"
#include "encoder.h"
int16_t AX, AY, AZ, GX, GY, GZ;
int8_t i, Duty = 0, Speed;

uint16_t AD_Value[2];

int8_t PWM_L, PWM_R;

void ps4(void)
{
	PWM_L = (20 - AD_Value[1] / 100 + (20 - AD_Value[0] / 100)) * 5;
	PWM_R = (20 - AD_Value[1] / 100 - (20 - AD_Value[0] / 100)) * 5;
	motor_set_pwm(PWM_L, PWM_R);
	//	// Y
	//	OLED_ShowNum(2, 3, AD_Value[0], 4);

	//	// X

	//	OLED_ShowNum(3, 3, AD_Value[1], 4);

	//	// PWM_L
	//	OLED_ShowSignedNum(4, 3, PWM_L, 3);

	//	// PWM_R

	//	OLED_ShowSignedNum(4, 9, PWM_R, 3);
}
int main(void)
{
	OLED_Init();

	//	OLED_ShowString(1, 1, "ID:");
	//	ID = MPU6050_GetID();
	//	OLED_ShowHexNum(1, 4, ID, 2);
	//
	Encoder1_Init();
	Encoder2_Init();
	MPU6050_Init();
	motor_Init();
	ADC_Config();
	OLED_ShowHexNum(1, 1, MPU6050_GetID(), 2);
	OLED_ShowString(2, 1, "x");
	OLED_ShowString(3, 1, "y");
	OLED_ShowString(4, 1, "z");

	while (1)
	{
		 ps4();
		//motor_set_pwm(30, 30);
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		//		OLED_ShowSignedNum(2, 3, AX, 5);
		//		OLED_ShowSignedNum(3, 3, AY, 5);
		//		OLED_ShowSignedNum(4, 3, AZ, 5);
		//		OLED_ShowSignedNum(2, 11, GX, 5);
		//		OLED_ShowSignedNum(3, 11, GY, 5);
		//		OLED_ShowSignedNum(4, 11, GZ, 5);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		// 在此处添加定时器中断处理代码
		OLED_ShowSignedNum(3, 4, Encoder1_Get(), 4);
		OLED_ShowSignedNum(4, 4, Encoder2_Get(), 4);

		OLED_ShowSignedNum(1, 4, PWM_L, 3);
		OLED_ShowSignedNum(1, 8, PWM_R, 3);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}