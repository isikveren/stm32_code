/*
 * @Author: isikveren lauxunzi@outlook.com
 * @Date: 2023-05-30 19:28:17
 * @LastEditors: isikveren lauxunzi@outlook.com
 * @LastEditTime: 2023-05-30 19:37:54
 * @FilePath: \51\key.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 *
 */
#include <REGX52.h>
#include "Delay.h"

unsigned char Key()
{
    unsigned char KeyNumber = 0;

    if (P3_1 == 0)
    {
        Delay(20);
        while (P3_1 == 0)
            ;
        Delay(20);
        KeyNumber = 1;
    }
    if (P3_0 == 0)
    {
        Delay(20);
        while (P3_0 == 0)
            ;
        Delay(20);
        KeyNumber = 2;
    }
    if (P3_2 == 0)
    {
        Delay(20);
        while (P3_2 == 0)
            ;
        Delay(20);
        KeyNumber = 3;
    }
    if (P3_3 == 0)
    {
        Delay(20);
        while (P3_3 == 0)
            ;
        Delay(20);
        KeyNumber = 4;
    }

    return KeyNumber;
}