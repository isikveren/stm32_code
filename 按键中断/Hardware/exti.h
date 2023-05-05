#ifndef __EXTI_H
#define __EXTI_H


void exti_init(void);	
void delay(__IO uint32_t nCount);
uint32_t get_sw(void);
uint32_t get_flag(void);

#endif