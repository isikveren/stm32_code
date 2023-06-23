#ifndef __L298N_H
#define __L298N_H
void Fan_Init(void);
void Fan_ON(void);

void Fan_OFF(void);
uint8_t Fan_Turn(void);
void Fan_SetSpeed(int8_t Speed);
#endif
