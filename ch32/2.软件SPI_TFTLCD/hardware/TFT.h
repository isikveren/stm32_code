#ifndef __TFT_H
#define __TFT_H
#include "ch32f10x.h"
#include "stdlib.h"
#define LCD_W 240
#define LCD_H 240
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define OLED_MODE 0
#define SIZE 16
#define XLevelL 0x00
#define XLevelH 0x10
#define Max_Column 128
#define Max_Row 64
#define Brightness 0xFF
#define X_WIDTH 128
#define Y_WIDTH 64

#define OLED_CMD 0
#define OLED_DATA 1

extern u16 BACK_COLOR, POINT_COLOR;

void Lcd_Init(void);
void LCD_Clear(u16 Color);
void Address_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_WR_DATA8(uint8_t da);
void LCD_WR_DATA(uint16_t da);
void LCD_WR_REG(uint8_t da);

void LCD_DrawPoint(u16 x, u16 y);
void LCD_DrawPoint_big(u16 x, u16 y);
u16 LCD_ReadPoint(u16 x, u16 y);
void Draw_Circle(u16 x0, u16 y0, u8 r);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color);
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 mode);
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len);
void LCD_Show2Num(u16 x, u16 y, u16 num, u8 len);
void LCD_ShowString(u16 x, u16 y, const u8 *p);

void showhanzi(unsigned int x, unsigned int y, unsigned char index);

#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40
#define BRRED 0XFC07
#define GRAY 0X8430
#define DARKBLUE 0X01CF
#define LIGHTBLUE 0X7D7C
#define GRAYBLUE 0X5458
#define LIGHTGREEN 0X841F
#define LGRAY 0XC618
#define LGRAYBLUE 0XA651
#define LBBLUE 0X2B12

#endif
