/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-03 18:32:41
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-06 20:31:37
 * @FilePath: \舵机\Hardware\ultrasonic.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/**
 * @FilePath     : /嵌入式代码/stm32/舵机/Hardware/ultrasonic.c
 * @Description  :
 * @Author       : isikveren lauxunzi@outlook.com
 * @Version      : 0.0.1
 * @LastEditors  : isikveren lauxunzi@outlook.com
 * @LastEditTime : 2023-06-03 18:37:31
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2023.
 **/
// #include "ultrasonic.h"
#include "ch32f10x.h"
#include "Delay.h"
#include "OLED.h"
// #include "ultrasonic.h"
int N = 0, count2 = 0;
uint16_t count_u = 0;
float distance = 0;
// void hcsr04_NVIC()
// {
//     NVIC_InitTypeDef NVIC_InitStructure;
//     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

//     NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//     NVIC_Init(&NVIC_InitStructure);
// }
void hcsr_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // GPIO初始化，定时器初始化，初始化外部中断

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能PB端口时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    // PB6-Trig(输入)所以PB6是输出模式 PB7-Echo(输出)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;        // Trig
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;     // Echo
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // 下拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 溢出时间tim=(arr+1)*(psc+1)/72000000	50000*72/72000000=500ms
    TIM_TimeBaseStructure.TIM_Period = 50000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

float Distance(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_6); // 预先拉低Trig引脚
    GPIO_SetBits(GPIOB, GPIO_Pin_6);
    Delay_us(20);
    GPIO_ResetBits(GPIOB, GPIO_Pin_6); // 发出10us的脉冲
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0)
        ; // 等待信号发出，信号发出，计数器置0,信号发出，变为高电平，引脚置1
          //    // N=0;
          //   TIM2->CNT = 0; // us级别读取
    TIM_SetCounter(TIM2, 0);
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 1)
        ; // 等待信号接受，信号发出过程中，引脚一直置位1
    count_u = TIM_GetCounter(TIM2);
    OLED_ShowNum(4, 1, count_u, 4);
    // 单位cm
    // v = 340m/s = 34000cm/s = 34000cm/10^6us = 0.034cm/us
    // s = vt/2 = t*0.034/2 = t*0.017 ≈ t/58
    distance = (float)count_u / 58;
    return distance;
}
// void TIM2_IRQHandler(void)
//{
//     if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//     {
//
//	} TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//		OLED_ShowNum(4,7,count2++,4);
//	//OLED_ShowNum(4,1,count,4);
//
// }
