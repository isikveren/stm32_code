#include "MySPI.h"

// CS -- PA4
// SCK -- PA5
// MISO -- PA6
// MOSI -- PA7
// RES --PB0
// DC -- PB1
void MySPI_W_SS(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}
void MySPI_W_SCK(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
}
uint8_t MySPI_W_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
}
void MySPI_W_MOSI(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
}
void MySPI_W_RES(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)BitValue);
}
void MySPI_W_DC(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)BitValue);
}
void MySPI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能A端口时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);            // 初始化GPIOA4,5,7

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);            // 初始化GPIOA6

    //  MySPI_W_SS(1); // 默认电平  模式3
    MySPI_W_SCK(1);
    // MySPI_W_MOSI(1);
}

void MySPI_Start(void)
{
    MySPI_W_SS(0);
}

void MySPI_Stop(void)
{
    MySPI_W_SS(1);
}
uint8_t MySPI_SwapByte(uint8_t ByteSend) // 串行数据写入
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {

        MySPI_W_SCK(0);
        MySPI_W_MOSI(ByteSend & 0x80);
        ByteSend <<= 1;
        MySPI_W_SCK(1);
        if (MySPI_W_MISO() == 1)
        {
            ByteSend |= 0x01;
        }
    }
    return ByteSend;
}

// uint8_t MySPI_SwapByte(uint8_t ByteSend) // 串行数据写入
// {
//     uint8_t i, ByteReceive = 0x00;

//     for (i = 0; i < 8; i++)
//     {

//         MySPI_W_SCK(0);
//         MySPI_W_MOSI(ByteSend & (0x80 >> i));
//         MySPI_W_SCK(1);
//         if (MySPI_W_MISO() == 1)
//         {
//             ByteReceive |= (0x80 >> i);
//         }
//     }
//     return ByteReceive;
// }
