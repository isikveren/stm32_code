#include <REGX52.H>

#include "delay.h"
unsigned char x[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
void Nixie_tube(unsigned char Location, unsigned char num)
{
    switch (Location)
    {
    case 1:
        P2_2 = 0;
        P2_3 = 0;
        P2_4 = 0;
        break;
    case 2:
        P2_2 = 1;
        P2_3 = 0;
        P2_4 = 0;
        break;
    case 3:
        P2_2 = 0;
        P2_3 = 1;
        P2_4 = 0;
        break;
    case 4:
        P2_2 = 1;
        P2_3 = 1;
        P2_4 = 0;
        break;
    case 5:
        P2_2 = 0;
        P2_3 = 0;
        P2_4 = 1;
        break;
    case 6:
        P2_2 = 1;
        P2_3 = 0;
        P2_4 = 1;
        break;
    case 7:
        P2_2 = 0;
        P2_3 = 1;
        P2_4 = 1;
        break;
    case 8:
        P2_2 = 1;
        P2_3 = 1;
        P2_4 = 1;
        break;

    default:
        break;
    }
    switch (num)
    {
    case 0:
        P0 = x[0];
        break;
    case 1:
        P0 = x[1];
        break;
    case 2:
        P0 = x[2];
        break;
    case 3:
        P0 = x[3];
        break;
    case 4:
        P0 = x[4];
        break;
    case 5:
        P0 = x[5];
        break;
    case 6:
        P0 = x[6];
        break;
    case 7:
        P0 = x[7];
        break;
    case 8:
        P0 = x[8];
        break;
    case 9:
        P0 = x[9];
        break;

    default:
        break;
    }
}

void main()
{

    unsigned char LEDNum = 0;
    unsigned char i = 0;

    while (1)
    {

        if (P3_1 == 0)
        {
            Delay(20);
            while (P3_1 == 0)
                ;
            Delay(20);
            i++;
            if (i == 9)
                i = 1;
        }
        if (P3_0 == 0)
        {
            Delay(20);
            while (P3_0 == 0)
                ;
            Delay(20);

            i--;
            if (i == 0)
                i = 8;
        }

        if (P3_2 == 0)
        {
            Delay(20);
            while (P3_2 == 0)
                ;
            Delay(20);

            LEDNum++;
            if (LEDNum > 9)
                LEDNum = 0;
        }

        if (P3_3 == 0)
        {
            Delay(20);
            while (P3_3 == 0)
                ;
            Delay(20);
            if (LEDNum == 0)
                LEDNum = 9;
            else
                LEDNum--;
        }
        Nixie_tube(i, LEDNum);
    }
}