/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-05 14:38:46
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-05 14:42:18
 * @FilePath: \project copy - 副本\Hardware\L298N.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __L298N_H
#define __L298N_H
void Fan_Init(void);
void Fan_ON(void);

void Fan_OFF(void);
uint8_t Fan_Turn(void);
void Fan_SetSpeed(int8_t Speed);
#endif
