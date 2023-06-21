/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-21 17:52:37
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-21 17:55:13
 * @FilePath: \平衡车\Hardware\motor.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"
#include "PWM.h"
void motor_Init(void);
void motor_set_pwm(int8_t PWM_L, int8_t PWM_R);
#endif
