/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-22 12:11:16
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-22 12:48:37
 * @FilePath: \平衡车\pid1.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
int count = 40;
float KP = 0.02f, KI = 0.05f, KD = 0.23f, cur_speed = 0, Pout, Iout, Dout, out, PWM = 0;

float err, last_err, i_err = 0;
void set_speed(float speed)
{
    err = speed - cur_speed;
    i_err += err;
    Pout = KP * err;
    Iout = KI * i_err;
    Dout = KD * (err - last_err);
    out = Pout + Iout + Dout;
    PWM += out;

    if (PWM > 100.0f)
    {
        PWM = 100.0f;
    }
    if (PWM < -100.0f)
    {
        PWM = -100.0f;
    }
}
int main()
{
    std::cout << cur_speed << "\t" << err << std::endl;
    for (int i = 0; i < count; i++)
    {
        /* code */
        cur_speed = PWM * 4;

        set_speed(-300);
        std::cout << cur_speed << "\t" << PWM << "\t" << err << std::endl;
    }
}