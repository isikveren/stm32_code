

/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-17 18:32:11
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-18 15:21:16
 * @FilePath: \7.IIC - MPU6050\Hardware\MPU6050.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MPU6050
#define __MPU6050
#include "stm32f10x.h"
#include "Delay.h"
#include "MyI2c.h"
#include "MPU6050_REG.h"
void MPU6050_Init(void);
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data); // 写数据
uint8_t MPU6050_ReadReg(uint8_t RegAddress);             // 读取一个字节

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ); // 读取数据
uint8_t MPU6050_GetID(void);

//int16_t MPU6050_temp(void);
#endif
