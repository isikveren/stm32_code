/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-06-10 18:08:58
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-06-10 18:13:29
 * @FilePath: \ADC\Hardware\OLED.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowChineseChar(uint8_t Line, uint8_t Column, uint8_t num);
void OLED_ShowChineseString(uint8_t Line, uint8_t Column, uint8_t num1, uint8_t num2);

#endif
