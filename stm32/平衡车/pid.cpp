#include <iostream>

float PWML, PWMR, cur_speed_L, cur_speed_R;
float errL, errR, errL_last = 0, errR_last = 0, integral_L = 0, integral_R = 0;
float Poutl = 0, Ioutl = 0, Doutl = 0, Poutr = 0, Ioutr = 0, Doutr = 0;

void motor_set_speed(float speedL, float speedR)
{
    float Kp = 0.2f, Ki = 0.01f, Kd = 0.1f;

    errL = speedL - cur_speed_L;
    errR = speedR - cur_speed_R;
    // P
    Poutl = Kp * errL;
    Poutr = Kp * errR;
    // I
    integral_L += errL;
    integral_R += errR;
    Ioutl = Ki * integral_L;
    Ioutr = Ki * integral_R;
    // D
    Doutl = Kd * (errL - errL_last);
    Doutr = Kd * (errR - errR_last);
    errL_last = errL;
    errR_last = errR;

    PWML = Poutl + Ioutl + Doutl;
    PWMR = Poutr + Ioutr + Doutr;

    if (PWML > 100.0f)
    {
        PWML = 100.0f;
    }
    if (PWML < -100.0f)
    {
        PWML = -100.0f;
    }
    if (PWMR > 100.0f)
    {
        PWMR = 100.0f;
    }
    if (PWMR < -100.0f)
    {
        PWMR = -100.0f;
    }
}
