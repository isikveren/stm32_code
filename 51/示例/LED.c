#include <REGX52.H>

#include "delay.h"

void main()
{

    unsigned char LEDNum = 0;

    while (1)
    {
#if 0
        if (P3_1 == 0)
        {
            P2_0 = 0;
        }
        else
        {
            P2_0 = 1;
        }

        if (P3_0 == 0)
        {
            P2_1 = 0;
        }
        else
        {
            P2_1 = 1;
        }
 
        if (P3_2 == 0)
        {
            P2_2 = 0;
        }
        else
        {
            P2_2 = 1;
        }
        if (P3_3 == 0)
        {
            P2_3 = 0;
        }
        else
        {
            P2_3 = 1;
        }
#endif
        if (P3_1 == 0)
        {
            Delay(20);
            while (P3_1 == 0)
                ;
            Delay(20);

            if (LEDNum >= 7)
            {
                LEDNum = 0;
            }
            else
            {
                LEDNum++;
            }
            P2 = ~(0x01 << LEDNum);
        }
        if (P3_0 == 0)
        {
            Delay(20);
            while (P3_0 == 0)
                ;
            Delay(20);

            if (LEDNum <= 0)
            {
                LEDNum = 7;
            }
            else
            {
                LEDNum--;
            }
            P2 = ~(0x01 << LEDNum);
        }
        P2 = ~(0x01 << LEDNum);
    }
}