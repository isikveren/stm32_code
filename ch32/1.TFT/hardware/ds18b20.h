#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "ch32f10x.h"
#include "Delay.h"
#include "io_bit.h"

/*  DS18B20时钟端口、引脚定义 */
#define DS18B20_PORT GPIOB
#define DS18B20_PIN (GPIO_Pin_15)
#define DS18B20_PORT_RCC RCC_APB2Periph_GPIOB

// IO操作函数
#define DS18B20_DQ_OUT PBout(15) // 数据端口
#define DS18B20_DQ_IN PBin(15)   // 数据端口

u8 DS18B20_Init(void);             // 初始化DS18B20
float DS18B20_GetTemperture(void); // 获取温度
void DS18B20_Start(void);          // 开始温度转换
void DS18B20_Write_Byte(u8 dat);   // 写入一个字节
u8 DS18B20_Read_Byte(void);        // 读出一个字节
u8 DS18B20_Read_Bit(void);         // 读出一个位
u8 DS18B20_Check(void);            // 检测是否存在DS18B20
void DS18B20_Reset(void);          // 复位DS18B20

#endif
