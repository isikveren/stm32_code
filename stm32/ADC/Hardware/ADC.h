/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-11 18:21:32
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-11 23:32:02
 * @FilePath: \ADC\Hardware\ADC.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __ADC_H
#define __ADC_H
#include "stm32f10x.h"
void ADC_Config(void);
uint16_t ADC_GetValue(void);
// void EXTI_Config(void);
#endif
