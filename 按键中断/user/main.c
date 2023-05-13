#include "stm32f10x.h"
//#include "Delay.h"

#include "Buzzer.h"
#include "Timer.h"
#include "Key.h"
#include "LED.h"
#include "OLED.h"
#include "string.h"
#include "exti.h"



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
		//flag = get_flag();
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

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        /* 延迟去抖 */
        delay(150000);
		if(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
		{
		 	flag++;
			play_notice_DOWN();
			OLED_ShowNum(1, 13, flag, 1);
		}

		while(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
		delay(150000);

        /* Clear the EXTI Line 13 */  
        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

void EXTI3_IRQHandler(void)
	{
	  if(EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        /* 延迟去抖 */
        delay(150000);
		if(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
		{
		 	sw++;
			play_notice_DOWN();
			OLED_ShowNum(1, 5, sw, 1);
		}

		while(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
		delay(150000);

        /* Clear the EXTI Line 13 */  
        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
