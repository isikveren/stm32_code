/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-21 20:02:33
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-21 21:01:34
 * @FilePath: \平衡车\Hardware\encoder.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __ENCODE_H_
#define __ENCODE_H_
#include "ch32f10x.h" // Device header
void Encoder1_Init(void);
void Encoder2_Init(void);
int16_t Encoder1_Get(void);
int16_t Encoder2_Get(void);
#endif
