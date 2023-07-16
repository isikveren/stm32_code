/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-18 15:27:18
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-07-12 08:48:04
 * @FilePath: \平衡车\user\main.c
 * @Description:
 */

#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include <string.h>
#include "ADC.h"
#include "MPU6050.h"
#include "string.h"
#include "Timer.h"
#include "motor.h"
#include "encoder.h"
#include <math.h>
#define M_PI 3.14159265358979323846

int16_t AX, AY, AZ, GX, GY, GZ, temp; // MPU6050输出的参数

uint16_t AD_Value[2];
uint32_t TIM1_i = 0, TIM2_i = 0, TIM1_j = 0;
float PWML, PWMR, cur_speed_L = 0, cur_speed_R = 0;
int turnment = 0;
double pitch;
int32_t zhili_out;
int32_t sudu_out;
int32_t zhuan_out;
int16_t PWM_OUT1;
int16_t PWM_OUT2;

// ps4摇杆控制PWM暂时不用
//  void ps4(void)
//  {
//  	PWML = (20 - AD_Value[1] / 100 + (20 - AD_Value[0] / 100)) * 5;
//  	PWMR = (20 - AD_Value[1] / 100 - (20 - AD_Value[0] / 100)) * 5;
//  }

void Smart_Car_Task(void)
{
	zhili_out = zhili(pitch, GY);
	// sudu_out = sudu(cur_speed_L, cur_speed_R);
	// zhuan_out = zhuan(turnment, GZ);
	PWM_OUT1 = zhili_out + sudu_out + zhuan_out;
	PWM_OUT2 = zhili_out + sudu_out - zhuan_out;
	if (PWM_OUT1 >= 1000)
	{
		PWM_OUT1 = 1000;
	}
	if (PWM_OUT1 <= -1000)
	{
		PWM_OUT1 = -1000;
	}
	if (PWM_OUT2 >= 1000)
	{
		PWM_OUT2 = 1000;
	}
	if (PWM_OUT2 <= -1000)
	{
		PWM_OUT2 = -1000;
	}
	if ((pitch >= 50) || (pitch <= -50))
	{
		PWM_OUT1 = 0;
		PWM_OUT2 = 0;
	}

	motor_set_pwm(PWM_OUT1, PWM_OUT2);
}

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	motor_Init();
	ADC_Config();
	OLED_ShowString(1, 1, "1");
	TIM1_Configuration();

	while (1)
	{
	}
}

// void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//	{
//		// 在这里执行中断处理的任务

//		// 清除中断标志位
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}

// // 定义 TIM1 更新中断的处理函数  5ms一次
void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		// 在这里执行中断处理的任务
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		pitch = atan((double)AX / (double)AZ) * (180.0 / M_PI);
		Smart_Car_Task();
		OLED_ShowSignedNum(1, 13, pitch, 3);

		// 清除中断标志位
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
