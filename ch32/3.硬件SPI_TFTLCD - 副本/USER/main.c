/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-18 15:27:18
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-22 14:08:28
 * @FilePath: \平衡车\user\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "ch32f10x.h"
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
#include <math.h>
#define DT 0.001f
int16_t AX, AY, AZ, GX, GY, GZ;
int32_t pitch;
int8_t i, Duty = 0, Speed;
uint16_t AD_Value[2];

// float angle, gyro; // 倾角和角速度
// float Kp = 12.0f, Ki = 1.0f, Kd = 0.2f;	  // PID控制参数
// float Pout, Iout, Dout;					  // PID控制输出
// float err = 0, err_last = 0, err_sum = 0; // PID控制误差项

float PWML, PWMR, cur_speed_L = 0, cur_speed_R = 0;
// float speedL_N, speedL_N;
void ps4(void)
{
	PWML = (20 - AD_Value[1] / 100 + (20 - AD_Value[0] / 100)) * 5;
	PWMR = (20 - AD_Value[1] / 100 - (20 - AD_Value[0] / 100)) * 5;
}
int main(void)
{
	OLED_Init();

	MPU6050_Init();
	motor_Init();
	ADC_Config();
	OLED_ShowHexNum(1, 1, MPU6050_GetID(), 2);
	OLED_ShowString(2, 1, "x");
	OLED_ShowString(3, 1, "y");
	OLED_ShowString(4, 1, "z");
	// motor_set_pwm(20, 20);
	while (1)
	{
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		cur_speed_L = Encoder2_Get();
		cur_speed_R = Encoder1_Get();
		//		OLED_ShowSignedNum(3, 4, cur_speed_L, 4);
		//		OLED_ShowSignedNum(4, 4, cur_speed_R, 4);

		//		OLED_ShowSignedNum(1, 4, PWML, 3);
		//		OLED_ShowSignedNum(1, 9, PWMR, 3);
		// // 在此处添加定时器中断处理代码
		// x 170  z 2080
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		GZ = AZ * 16000 / 32768;
		pitch = atan2(AX, AZ);
		OLED_ShowSignedNum(2, 3, AX, 5);
		OLED_ShowSignedNum(3, 3, AY, 5);
		OLED_ShowSignedNum(4, 3, AZ, 5);
		//				OLED_ShowSignedNum(2, 11, GX, 5);
		//				OLED_ShowSignedNum(3, 11, GY, 5);
		//				OLED_ShowSignedNum(4, 11, GZ, 5);

		OLED_ShowSignedNum(2, 10, GZ, 5);
		OLED_ShowSignedNum(3, 10, pitch, 5);

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}