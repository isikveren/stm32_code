#include <REGX52.h>
#include "MatrixKey.h"
#include "LCD1602.h"
unsigned char KeyNum;

unsigned int Password = 0, count = 4;
int main(void)
{
    LCD_Init();
    LCD_ShowString(1, 1, "Password:");

    while (1)
    {
        KeyNum = MatrixKey();
        if (KeyNum)
        {
            if (KeyNum <= 10)
            {
                if (count > 0)
                {
                    Password *= 10;
                    Password += KeyNum % 10;
                    LCD_ShowNum(2, 1, Password, 4);
                    count--;
                }
            }
            if (KeyNum == 11)
            {
                if (Password == 1234)
                {
                    LCD_ShowString(1, 10, "OK");
                }
                else
                {
                    LCD_ShowString(1, 10, "ERROR");
                }
            }
            if (KeyNum == 12)
            {
                Password = 0;
                count = 4;
                LCD_ShowNum(2, 1, Password, 4);
                LCD_ShowString(1, 10, "     ");
            }
        }
    }
}