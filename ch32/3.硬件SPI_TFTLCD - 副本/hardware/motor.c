/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-21 17:52:42
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-22 13:04:08
 * @FilePath: \平衡车\Hardware\motor.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 *
 */
#include "motor.h"
#include "encoder.h"
extern float PWML, PWMR, cur_speed_L, cur_speed_R;
float errL, errR, errL_last = 0, errR_last = 0, integral_L = 0, integral_R = 0;
float Poutl = 0, Ioutl = 0, Doutl = 0, Poutr = 0, Ioutr = 0, Doutr = 0, outl, outr;

float KP = 0.02f, KI = 0.05f, KD = 0.23f, cur_speed = 0, Pout, Iout, Dout, out;
float err, last_err, i_err = 0;
void motor_Init(void)
{
    PWM_Init();
    Encoder1_Init();
    Encoder2_Init();
}
void motor_set_pwm(int8_t PWM_L, int8_t PWM_R)
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

// void motor_set_speed(float speedL, float speedR)
// {
//     float Kp = 0.02f, Ki = 0.05, Kd = 0.023f;

//     errL = speedL - cur_speed_L;
//     errR = speedR - cur_speed_R;
//     // P
//     Poutl = Kp * errL;
//     Poutr = Kp * errR;
//     // I
//     integral_L += errL;
//     integral_R += errR;
//     Ioutl = Ki * integral_L;
//     Ioutr = Ki * integral_R;
//     // D
//     Doutl = Kd * (errL - errL_last);
//     Doutr = Kd * (errR - errR_last);
//     errL_last = errL;
//     errR_last = errR;

//     outl = Poutl + Ioutl + Doutl;
//     outr = Poutr + Ioutr + Doutr;

//     PWML += outl;
//     PWMR += outr;
//     if (PWML > 100.0f)
//     {
//         PWML = 100.0f;
//     }
//     if (PWML < -100.0f)
//     {
//         PWML = -100.0f;
//     }
//     if (PWMR > 100.0f)
//     {
//         PWMR = 100.0f;
//     }
//     if (PWMR < -100.0f)
//     {
//         PWMR = -100.0f;
//     }
//     motor_set_pwm(PWML, PWMR);
// }

// void set_speed(float speed)
// {
//     err = speed - cur_speed_L;
//     i_err += err;
//     Pout = KP * err;
//     Iout = KI * i_err;
//     Dout = KD * (err - last_err);
//     out = Pout + Iout + Dout;
//     PWML += out;

//     if (PWML > 100.0f)
//     {
//         PWML = 100.0f;
//     }
//     if (PWML < -100.0f)
//     {
//         PWML = -100.0f;
//     }

//     motor_set_pwm(PWML, 0);

// }
