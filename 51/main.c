#include <REGX52.h>
#include "MatrixKey.h"
#include "LCD1602.h"
#include "delay.h"
unsigned char KeyNum, LEDNum = 0;

unsigned int Password = 0, count = 4, flag = 1;
int main(void)
{
    LCD_Init();
    LCD_ShowString(1, 1, "CLOCK:");

    while (1)
    {
        KeyNum = MatrixKey();
        if (KeyNum)
        {

            if (KeyNum == 11)
            {
                flag++;
            }
            if (KeyNum == 12)
            {
                flag--;
            }
        }

        if (flag % 2 == 0)
        {
            if (LEDNum <= 0)
            {
                LEDNum = 7;
            }
            else
                LEDNum--;
        }
        else
        {
            if (LEDNum >= 7)
            {
                LEDNum = 0;
            }
            else
                LEDNum++;
        }

        P2 = ~(0x01 << LEDNum);

        Delay(300);
    }
}
