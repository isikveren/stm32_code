/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-11 18:21:27
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-13 13:34:13
 * @FilePath: \ADC\Hardware\ADC.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "ADC.h"
// uint16_t AD_Value[2];
void ADC_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能 GPIO 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  // 使能 ADC 时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    // 使能 DMA 时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                     // ADC时钟分频 72/6=12Mhz

    GPIO_InitTypeDef GPIO_InitStructure;
    // 配置 GPIOA0（ADC2 输入通道 0）为模拟输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); // 通道 0
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5); // 通道 1
    ADC_InitTypeDef ADC_InitStructure;

    // 初始化 ADC
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;       // 扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // 连续模式打开

    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 不使用外部触发 使用内部软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              // 右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 2;                             // 转换通道数目为 2
    ADC_Init(ADC1, &ADC_InitStructure);
    // 配置 ADC1
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_InitTypeDef DMA_InitStructure;

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;             // 指定待读或待写的外设的首地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 指定外设数据宽度，以字节传输
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            // 外设地址不自增
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;                  // DMA 通道数据传输操作的目标地址
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         // 以字节传输
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     // 存储器地址自增

    DMA_InitStructure.DMA_BufferSize = 2;                 // DMA 传输的缓存大小
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;    // 外设站点作为数据源
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;          // （Memory to Memory）模式 不使用软件触发
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;       // 循环和一般模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; // 优先级
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
    // 启用 ADC1

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET)
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET)
        ;
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

// 连续转换非扫描
/*
void ADC_Config(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能 GPIO 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  // 使能 ADC 时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                     // ADC时钟分频 72/6=12Mhz

    GPIO_InitTypeDef GPIO_InitStructure;
    // 配置 GPIOA0（ADC2 输入通道 0）为模拟输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_InitTypeDef ADC_InitStructure;

    // 初始化 ADC
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       // 单通道模式
                                                                        // ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 // 单次转换
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                  // 连续转换转换
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 不使用外部触发 使用内部软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              // 右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             // 转换通道数目为 1
    ADC_Init(ADC1, &ADC_InitStructure);
    // 配置 ADC1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); // 通道 0

    // 启用 ADC1
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET)
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET)
        ;
    // 启动 ADC 转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

uint16_t ADC_GetValue(void)
{

    // 等待转换完成
    //  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET)
    ;
    // 返回结果值
    return ADC_GetConversionValue(ADC1);
}
**/