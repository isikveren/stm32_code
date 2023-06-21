/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-21 17:52:42
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-21 18:08:55
 * @FilePath: \平衡车\Hardware\motor.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 *
 */
#include "motor.h"
void motor_Init(void)
{
    PWM_Init();
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
