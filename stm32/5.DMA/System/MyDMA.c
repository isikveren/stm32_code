/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-12 23:36:33
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-13 12:17:56
 * @FilePath: \DMA\System\MyDma.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "MyDMA.h"

uint16_t MyDMA_Size;
void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
    MyDMA_Size = Size;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_InitTypeDef DMA_InitStructure;

    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;                       // 指定待读或待写的外设的首地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 指定外设数据宽度，以字节传输
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;         // 外设地址应该自动增加
    DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;                           // DMA 通道数据传输操作的目标地址
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // 以字节传输
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // 存储器地址自增

    DMA_InitStructure.DMA_BufferSize = Size;              // DMA 传输的缓存大小
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;    // 外设站点作为数据源
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;           // （Memory to Memory）模式
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;         // 循环和一般模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; // 优先级
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel1, DISABLE);
}
void MyDMA_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);
    DMA_Cmd(DMA1_Channel1, ENABLE);

    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET)
    {
    }
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
