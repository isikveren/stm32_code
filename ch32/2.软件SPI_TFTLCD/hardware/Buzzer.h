#ifndef __BUZZER_H
#define __BUZZER_H

void Buzzer_Init(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);
void Buzzer_Turn(void);
void Buzzer_1000Hz(void);
void Buzzer_100Hz(void);
void Buzzer_10000Hz(void);

void Buzzer_us(int n,int m);
void play(void);

void play_notice_UP(void);
void play_notice_DOWN(void);
#endif
