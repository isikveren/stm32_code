/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-12 23:36:33
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-12 23:55:19
 * @FilePath: \DMA\System\MyDma.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "MyDMA.h"
void MyDMA_Init(uint32_t AddrA)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_InitTypeDef DMA_InitStructure;

    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;  //指定待读或待写的外设的首地址
    DMA_InitStructure.DMA_PeripheralDataSize = ;  //指定外设数据宽度
    DMA_InitStructure.DMA_PeripheralInc = ;
    DMA_InitStructure.DMA_MemoryBaseAddr = ;
    DMA_InitStructure.DMA_MemoryDataSize = ;
    DMA_InitStructure.DMA_MemoryInc = ;

    DMA_InitStructure.DMA_BufferSize = ;
    DMA_InitStructure.DMA_DIR = ;
    DMA_InitStructure.DMA_M2M = ;
    DMA_InitStructure.DMA_Mode = ;
    DMA_InitStructure.DMA_Priority = ;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
}