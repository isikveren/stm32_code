/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-07-14 07:55:36
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-07-14 07:58:02
 * @FilePath: \机智云\hardware\usart3.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */



#ifndef __USART3_H
#define __USART3_H

#include <stdio.h>

#include "ch32f10x.h"

void usart3_init(void);
int32_t usart3Write(uint8_t *buf, uint32_t len);
#endif