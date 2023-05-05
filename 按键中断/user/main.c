#include "stm32f10x.h"
//#include "Delay.h"

#include "Buzzer.h"
#include "Timer.h"
#include "Key.h"
#include "LED.h"
#include "OLED.h"
#include "string.h"
#include "exti.h"

void Light(uint8_t m);
void Key_Init(void);
uint8_t Key_GetNum(void);
void LED_Init(void);

uint8_t sw = 0;
	uint8_t KeyNum;
    uint8_t count = 0;
    uint8_t flag = 0;

int main(void)
{
	exti_init();
    Key_Init();
    Buzzer_Init();
    LED_Init();
   
    OLED_Init();
    OLED_ShowString(1, 1, "sw:   flag:");
    OLED_ShowString(2, 1, "count:");

    while (1)
    {
		flag = get_flag();
        if (flag %2== 0)
        {
            count++;
        }
        else
        {
            count--;
        }
        count = count % 100;
		
        OLED_ShowNum(1, 5, sw, 1);
        OLED_ShowNum(1, 13, flag, 1);
        OLED_ShowNum(2, 13, count, 2);
		delay(5000000);
       // Delay_ms(100);
    }
}


