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

void OLED_Display_Turn(uint8_t i);
void OLED_Display_Color(uint8_t i);
void OLED_Display_Dir(uint8_t Dirx, uint8_t Diry);
void OLED_ShowChar_new(uint8_t Line, uint8_t Column, char Char);

void OLED_ShowBMP(uint8_t Line, uint8_t Column, uint8_t Line_end, uint8_t Column_end, uint8_t BMP[]);
#endif
