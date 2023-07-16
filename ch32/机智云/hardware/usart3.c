/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-07-14 07:55:04
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-07-14 23:52:31
 * @FilePath: \机智云\hardware\Usart3.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AEE
 */

#include "gizwits_product.h"
#include "usart3.h"
void usart3_init(void)
{
    // 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // 配置GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;      // TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;    // RX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // USART配置
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控制
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;         // 校验位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      // 停止位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 字长8位
    USART_Init(USART3, &USART_InitStructure);
    // 中断配置
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // 接收数据不为空时 ，开启中断

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中断分组

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    // 开启串口
    USART_Cmd(USART3, ENABLE);
}

void USART3_IRQHandler(void)
{
    uint8_t value = 0;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {

        USART_ClearITPendingBit(USART3, USART_IT_RXNE);

        value = USART_ReceiveData(USART3);
        gizPutData(&value, 1);
    }
}

int32_t usart3Write(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    if (NULL == buf)
    {
        return -1;
    }
    for (i = 0; i < len; i++)
    {
        USART_SendData(USART3, buf[i]);
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
            ;
        if (i >= 2 && buf[i] == 0xFF)
        {
            USART_SendData(USART3, 0x55);
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
                ;
        }
    }
    return len;
}