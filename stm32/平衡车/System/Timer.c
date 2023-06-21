/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-18 15:27:18
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-21 20:03:35
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
extern int num;
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	// // 编码器GPIO
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// GPIO_InitTypeDef GPIO_InitStructure;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_Init(GPIOA, &GPIO_InitStructure);
	// // 编码器GPIO
	TIM_InternalClockConfig(TIM3);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65535 - 1;				// ARR自动重装器
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;				// PSC预分频器的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	// // 编码器输入捕获单元
	// TIM_ICInitTypeDef TIM_ICInitStructure;
	// TIM_ICStructInit(&TIM_ICInitStructure);
	// TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	// TIM_ICInitStructure.TIM_ICFilter = 0xF;
	// // TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	// TIM_ICInit(TIM3, &TIM_ICInitStructure);
	// TIM_ICStructInit(&TIM_ICInitStructure);
	// TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	// TIM_ICInitStructure.TIM_ICFilter = 0xF;
	// // TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;

	// TIM_ICInit(TIM3, &TIM_ICInitStructure);

	// TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	// // 编码器输入捕获单元

	// 中断配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM3, ENABLE);
}
