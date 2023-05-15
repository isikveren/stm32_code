#ifndef __STM32F103C8T6_GPIO_H
#define __STM32F103C8T6_GPIO_H

#include "stm32f103c8t6.h"

#define GPIO_Pin_0 ((uint16_t)0x0001)   /*!< Pin 0 selected */
#define GPIO_Pin_1 ((uint16_t)0x0002)   /*!< Pin 1 selected */
#define GPIO_Pin_2 ((uint16_t)0x0004)   /*!< Pin 2 selected */
#define GPIO_Pin_3 ((uint16_t)0x0008)   /*!< Pin 3 selected */
#define GPIO_Pin_4 ((uint16_t)0x0010)   /*!< Pin 4 selected */
#define GPIO_Pin_5 ((uint16_t)0x0020)   /*!< Pin 5 selected */
#define GPIO_Pin_6 ((uint16_t)0x0040)   /*!< Pin 6 selected */
#define GPIO_Pin_7 ((uint16_t)0x0080)   /*!< Pin 7 selected */
#define GPIO_Pin_8 ((uint16_t)0x0100)   /*!< Pin 8 selected */
#define GPIO_Pin_9 ((uint16_t)0x0200)   /*!< Pin 9 selected */
#define GPIO_Pin_10 ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define GPIO_Pin_11 ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define GPIO_Pin_12 ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define GPIO_Pin_13 ((uint16_t)0x2000)  /*!< Pin 13 selected */
#define GPIO_Pin_14 ((uint16_t)0x4000)  /*!< Pin 14 selected */
#define GPIO_Pin_15 ((uint16_t)0x8000)  /*!< Pin 15 selected */
#define GPIO_Pin_All ((uint16_t)0xFFFF) /*!< All pins selected */

typedef enum
{
    GPIO_Speed_10MHz = 1, // 10MHz (01)b
    GPIO_Speed_2MHz,      // 2MHz (10)b
    GPIO_Speed_50MHz      // 50MHz (11)b
} GPIOSpeed_Typedef;

typedef enum
{
    GPIO_Mode_Ain = 0x0,
    GPIO_Mode_IN_FLOATING = 0x04,
    GPIO_Mode_IPD = 0x28,
    GPIO_Mode_IPU = 0x48,

    GPIO_Mode_OUT_OD = 0x14,
    GPIO_Mode_OUT_PP = 0x10,
    GPIO_Mode_AF_OD = 0x1c,
    GPIO_Mode_AF_PP = 0x18
} GPIOMode_Typedef;

typedef struct
{
    uint16_t GPIO_Pin;
    uint16_t GPIO_Speed;
    uint16_t GPIO_Mode;
} GPIO_InitTypeDef;

void GPIO_SetBits_2(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits_2(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
#endif
