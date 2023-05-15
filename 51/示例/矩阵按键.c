#include <REGX52.h>
#include "MatrixKey.h"

unsigned char KeyNum;
int main(void)
{
    LCD_Init();
    LCD_ShowString(1, 1, "MatrixKey:");

    unsigned int Password = 0, count = 4;
    while (1)
    {
        KeyNum = MatrixKey();
        if (KeyNum)
        {
            if (KeyNum <= 10 && count--)
            {
                Password *= 10;
                Password += KeyNum % 10;
                LCD_ShowNum(2, 1, Password, 4);
            }
        }
    }
}