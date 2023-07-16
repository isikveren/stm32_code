/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-18 15:27:18
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-07-10 06:39:22
 * @FilePath: \平衡车\System\Timer.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-03 11:48:37
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-21 20:00:31
 * @FilePath: \小车\System\Timer.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h" // Device header

void TIM1_Configuration(void)
{
	// 使能定时器 TIM1 的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_InternalClockConfig(TIM1);
	// 配置 TIM1 的基本参数
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 3600 - 1;					// 设置计数器周期为 3600
	TIM_TimeBaseStructure.TIM_Prescaler = 20 - 1;				// 设置预分频值为 20
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 设置计数模式为向上计数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 设置时钟分频为 1
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	// 使能 TIM1 更新中断
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	// 配置 NVIC 中断优先级，并使能中断
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;		  // 中断通道为 TIM1 更新中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 设置抢占优先级为 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  // 设置子优先级为 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// 启动 TIM1
	TIM_Cmd(TIM1, ENABLE);
}
