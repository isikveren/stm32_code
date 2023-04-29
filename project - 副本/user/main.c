#include "stm32f10x.h"
#include "Delay.h"

#include "Buzzer.h"
#include "Timer.h"
#include "Key.h"
#include "LED.h"
#include "string.h"

void  Light(uint8_t m);
void Key_Init(void);
uint8_t Key_GetNum(void);
void LED_Init(void);

int main(void)
{

    Key_Init();
    Buzzer_Init();

    LED_Init();
    uint8_t KeyNum;
    uint8_t count = 0;
    uint8_t flag = 0;
    uint8_t flag2 = 0;
    while (1)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
        KeyNum = Key_GetNum();
        if (KeyNum == 1)
        {
            play_notice_UP();
            if (flag2)
                flag2 = 0;
            else
                flag2 = 1;
        }
        if (flag2)
        {
            if (KeyNum == 2)
            {
                play_notice_DOWN();
                if (flag)
                    flag = 0;
                else
                    flag = 1;
            }
            if (flag)
            {
                count -= 1;
            }
            else
            {
                count += 1;
            }
            Light(count % 4);
            Delay_ms(400);
        }
    }
}

void Light(uint8_t m)
{
    switch (m)
    {
    case 0:
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        break;
    case 1:
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        break;
    case 2:
        GPIO_ResetBits(GPIOA, GPIO_Pin_2);
        break;
    case 3:
        GPIO_ResetBits(GPIOA, GPIO_Pin_3);
        break;
        //	default:GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);break;
    }

}
