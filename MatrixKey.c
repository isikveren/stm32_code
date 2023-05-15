#include <REGX52.h>
#include "Delay.h"
/**
 *@brief 矩阵键盘扫描，读取按键键码
 *@param   空
 *@retval   KeyNumber
 按键按下不放，程序会停留在此函数，松手则返回键码，没有按键按下返回0.
 */
unsigned char MatrixKey()
{
    unsigned char KeyNumber = 0;
    P1 = 0xFF;
    P1_3 = 0;
    if (P1_7 == 0)
    {
        Delay(20);
        while (P1_7 == 0)
            ;
        Delay(20);
        KeyNumber = 1;
    }
    if (P1_6 == 0)
    {
        Delay(20);
        while (P1_7 == 0)
            ;
        Delay(20);
        KeyNumber = 5;
    }
    if (P1_5 == 0)
    {
        Delay(20);
        while (P1_7 == 0)
            ;
        Delay(20);
        KeyNumber = 9;
    }
    if (P1_4 == 0)
    {
        Delay(20);
        while (P1_7 == 0)
            ;
        Delay(20);
        KeyNumber = 13;
    }

    return KeyNumber;
}