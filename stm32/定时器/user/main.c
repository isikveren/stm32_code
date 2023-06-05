#include "stm32f10x.h"

#include "Buzzer.h"
#include "Timer.h"
#include "Key.h"
#include "OLED.h"
#include "string.h"
#include "exti.h"

uint8_t sw = 1;
uint8_t KeyNum;
uint8_t count = 1;
uint8_t flag = 1;
void stars(uint8_t count);
int main(void)
{
    exti_init();
    Key_Init();
    Buzzer_Init();

    Timer_Init();
    OLED_Init();
    OLED_ShowString(1, 1, "sw:   flag:");
    OLED_ShowString(2, 1, "count:");
    OLED_ShowNum(1, 12, flag, 1);
    OLED_ShowNum(1, 5, sw, 1);
    while (1)
    {
        if (sw)
        {
            stars(count);
        }
        else
        {
            stars(5);
        }
    }
}
void stars(uint8_t count)
{
    switch (count)
    {
    case 1:
        OLED_ShowString(3, 3, "*      ");
        break;
    case 2:
        OLED_ShowString(3, 3, "  *    ");
        break;
    case 3:
        OLED_ShowString(3, 3, "    *  ");
        break;
    case 4:
        OLED_ShowString(3, 3, "      *");
        break;
    case 5:
        OLED_ShowString(3, 3, "       ");
        break;
    default:
        break;
    }
}

void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        /* 延迟去抖 */
        delay(150000);
        if (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
        {
            if (flag)
                flag = 0;
            else
                flag = 1;

            OLED_ShowNum(1, 12, flag, 3);
        }

        while (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
            delay(150000);

        /* Clear the EXTI Line 13 */
        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        /* 延迟去抖 */
        delay(150000);
        if (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
        {
            if (sw)
                sw = 0;
            else
                sw = 1;

            OLED_ShowNum(1, 5, sw, 1);
        }

        while (0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
            delay(150000);

        /* Clear the EXTI Line 13 */
        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        if (sw)
        {
            if (flag)
            {
                count++;
                if (count > 4)
                {
                    count = 1;
                }
            }
            else
            {
                count--;
                if (count < 1)
                {
                    count = 4;
                }
            }
        }
    }
}