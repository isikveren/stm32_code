#include "debug.h"
void LED_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // ÍÆÍìÊä³ö
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_SetBits(GPIOC, GPIO_Pin_13);

}
int main(void)
{
    LED_Init();
	Delay_Init();

	while(1){
	    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	    Delay_Ms(500);
	    GPIO_SetBits(GPIOC, GPIO_Pin_13);
	    Delay_Ms(500);
	}
}

