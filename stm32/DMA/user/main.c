
#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "key.h"
#include "ultrasonic.h"
#include "Buzzer.h"
#include "Timer.h"
#include "IC.h"
#include "LED.h"
#include "ADC.h"
uint8_t DataA[] = {0x01, 0x02, 0x03, 0x04};
uint8_t DataB[] = {0, 0, 0, 0};

int main(void)
{
	OLED_Init();
	// OLED_ShowChineseString(1, 1, 0, 4);
	OLED_ShowString(1, 1, "DMA:");

	while (1)
	{
	}
}
