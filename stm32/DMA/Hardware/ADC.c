/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-11 18:21:27
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-11 23:34:08
 * @FilePath: \ADC\Hardware\ADC.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "ADC.h"

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
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;       // 单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 单次转换

    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 不使用外部触发 使用内部软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              // 右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             // 转换通道数目为 1
    ADC_Init(ADC1, &ADC_InitStructure);
    // 配置 ADC1

    // 启用 ADC1
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET)
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET)
        ;
}

uint16_t ADC_GetValue(uint8_t ADC_Channel)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5); // 通道 0
    // 启动 ADC 转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    // 等待转换完成
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET)
        ;
    // 返回结果值
    return ADC_GetConversionValue(ADC1);
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