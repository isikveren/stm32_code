
#include "stm32f10x.h"
#include "Buzzer.h"
#include "exti.h"
#include "OLED.h"
uint8_t sw2 = 0;
uint8_t flag2 = 0;
void delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--);
}


void exti_init(void)
{
    // 开启时钟
	
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    // 配置GPIO

//key1
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    // 配置EXTI
	/* 将KEY1 按键配置为中断模式，下降沿触发中断 */    
  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	
		//key1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    /* 将KEY1 按键配置为中断模式，下降沿触发中断 */    
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;			   //中断线
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		 //中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* 将KEY1 按键的中断优先级配置为最低 */  
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;	 //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;   //抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		  //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);				 //根据NVIC_InitStructure中指定的参数初始化外设NVIC
	
	//key2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
    /* 将KEY2 按键配置为中断模式，下降沿触发中断 */    
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;			   //中断线
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		 //中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* 将KEY2 按键的中断优先级配置为最低 */  
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	 //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;   //抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		  //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);				 //根据NVIC_InitStructure中指定的参数初始化外设NVIC
	
}


uint32_t get_sw(void)
{
	return sw2;
}

uint32_t get_flag(void)
{
	return flag2;
}

void EXTI3_IRQHandler(void)
	{
	  if(EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        /* 延迟去抖 */
        delay(150000);
		if(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
		{
		 	sw2++;
			play_notice_DOWN();
		}

		while(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
		delay(150000);

        /* Clear the EXTI Line 13 */  
        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
        EXTI_ClearITPendingBit(EXTI_Line0);
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
		 	flag2++;
			play_notice_DOWN();
			OLED_ShowNum(1, 13, flag2, 1);
		}

		while(0 == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
		delay(150000);

        /* Clear the EXTI Line 13 */  
        /* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}