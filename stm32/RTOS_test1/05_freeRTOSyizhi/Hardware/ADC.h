/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-13 12:39:42
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-13 13:34:19
 * @FilePath: \DMA+ADC - 多通道\Hardware\ADC.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef __ADC_H
#define __ADC_H
#include "stm32f10x.h"
extern uint16_t AD_Value[2];
void ADC_Config(void);

// void EXTI_Config(void);
#endif
