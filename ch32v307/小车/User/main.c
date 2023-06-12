
#include "debug.h"
// #include "system.h"
#include "PWM.h"
#include "LED.h"
// #include "OLED.h"ÄãºÃ
int t = 10000,i;

uint8_t Keynum, sw =0;
void set_speed(int left, int right)
{
    if(left>=0){
        PWM_SetCompare1(left);
        PWM_SetCompare3(0);
    }else if(left<0){
        PWM_SetCompare1(0);
       PWM_SetCompare3(-left);
      //  PWM_SetCompare3(0);
    }
    if(right>=0){
        PWM_SetCompare2(right);
        PWM_SetCompare4(0);
     }else if(right<0){
         PWM_SetCompare2(0);
         PWM_SetCompare4(-right);
      //   PWM_SetCompare4(0);
     }

}
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t key(void)
{
    uint8_t KeyNum = 0;
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
    {
        Delay_Ms(20);
        while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
            ;
        Delay_Ms(20);
        KeyNum = 1;
    }
    return KeyNum;
}

int main(void)
{
    LED_Init();
    Delay_Init();
    // OLED_Init();
    PWM_Init();
    KEY_Init();

    while (1)
    {
        Keynum = key();
        if (Keynum == 1)
        {
            sw = (sw == 1) ? 0 : 1;
        }

        if (sw==1)
        {
            GPIO_ResetBits(GPIOA, GPIO_Pin_4);
            set_speed(60, 60);
            Delay_Ms(1000);
            set_speed(60, -60);
            Delay_Ms(2000);
//            Delay_Ms(1000);


            sw=0;
        }
        else
        {
            set_speed(0, 0);
            GPIO_SetBits(GPIOA, GPIO_Pin_4);
        }


    }
}
