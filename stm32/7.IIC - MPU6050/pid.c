/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-18 15:28:10
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-18 15:28:15
 * @FilePath: \7.IIC - MPU6050\pid.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stdio.h"
#include "stdlib.h"
#include "stm32f10x.h"
#include "motor.h"
#include "mpu6050.h"
#define DT 0.001f
float angle, gyro;                        // 倾角和角速度
float Kp = 12.0f, Ki = 1.0f, Kd = 0.2f;   // PID控制参数
float Pout, Iout, Dout;                   // PID控制输出
float err = 0, err_last = 0, err_sum = 0; // PID控制误差项
float pwm_value_L, pwm_value_R;           // 左右电机的PWM值
void TIM2_IRQHandler(void)                // 100Hz  10ms
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
        mpu_dmp_get_data(&angle, &gyro, DT); // 获取倾角和角速度
        err = 0 - angle;                     // 计算误差项
        err_sum += err * DT;
        Pout = Kp * err;
        Iout = Ki * err_sum;
        Dout = Kd * (err - err_last) / DT;
        err_last = err;
        pwm_value_L = Pout + Iout + Dout; // 计算左右电机的PWM值
        pwm_value_R = Pout + Iout + Dout;
        motor_set_pwm(pwm_value_L, pwm_value_R); // 设置左右电机的PWM值
    }
}
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    mpu_init();
    motor_init();
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 7199;  // 7200
    TIM_TimeBaseStructure.TIM_Prescaler = 99; // 100
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM2, ENABLE);
    while (1)
    {
        // 系统将在中断中运行，这里不需要执行其他操作
    }
}