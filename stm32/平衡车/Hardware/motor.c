
/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-21 17:52:42
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-07-12 08:50:46
 * @FilePath: \平衡车\Hardware\motor.c
 * @Description: 电机驱动以及PID控制速度环 直立环
 */

#include "motor.h"
#include "encoder.h"
float zhili_kp = -100.4, zhili_kd = 0, sudu_kp = 0, sudu_ki = 0, zhuan_kd = 0, zhuan_kp = 0;
float car_zero = 0;
int32_t movement = 0;
int32_t Encoder_Integral = 0;
extern int32_t pitch;

void motor_Init(void)
{
    PWM_Init();
    Encoder1_Init();
    Encoder2_Init();
}
void motor_set_pwm(int16_t PWM_R, int16_t PWM_L)
{
    if (PWM_R > 0)
    {
        PWM_SetCompare1(0);
        PWM_SetCompare2(PWM_R);
    }
    else if (PWM_R <= 0)
    {
        PWM_SetCompare1(-PWM_R);
        PWM_SetCompare2(0);
    }

    if (PWM_L > 0)
    {
        PWM_SetCompare3(PWM_L);
        PWM_SetCompare4(0);
    }
    else if (PWM_L <= 0)
    {
        PWM_SetCompare3(0);
        PWM_SetCompare4(-PWM_L);
    }
}

/**
 * @description: 直立环PD控制
 * @param {float} angle 测到的角度
 * @param {float} gryo 测到的角速度
 * @return {*}PWM
 */
int32_t zhili(float angle, float gryo)
{
    float err;
    int32_t pwm_zhili;
    err = car_zero - angle; // 期望角度-当前角度
    pwm_zhili = zhili_kp * err + zhili_kd * gryo;
    return pwm_zhili;
}

/**
 * @description: 速度环 PI控制
 * @param {int16_t} encoder_left 左轮编码器速度
 * @param {int16_t} encoder_right 右轮编码器速度
 * @return {*}PWM
 */
int32_t sudu(int16_t encoder_left, int16_t encoder_right)
{
    static int32_t pwm_sudu, Encoder_Least, Encoder;
    Encoder_Least = (encoder_left + encoder_right) - movement;
    Encoder *= 0.8;
    Encoder += Encoder_Least * 0.2;
    Encoder_Integral += Encoder;
    if (Encoder_Integral > 8000)
        Encoder_Integral = 8000;
    if (Encoder_Integral < -8000)
        Encoder_Integral = 8000;

    pwm_sudu = sudu_kp * Encoder + sudu_ki * Encoder_Integral;
    if ((pitch >= 60) || (pitch <= -60))
    {
        Encoder_Integral = 0;
    }
    return pwm_sudu;
}

int32_t zhuan(float set_turn, float gz)
{
    int pwm_out = 0;
    if (set_turn == 0)
    {
        pwm_out = zhuan_kd * gz;
    }
    if (set_turn != 0)
    {
        pwm_out = zhuan_kp * set_turn;
    }

    return pwm_out;
}
