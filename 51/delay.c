
#include <INTRINS.H>

void Delay500ms() //@12.000MHz
{
    unsigned char i, j, k;

    _nop_();
    i = 4;
    j = 205;
    k = 187;
    do
    {
        do
        {
            while (--k)
                ;
        } while (--j);
    } while (--i);
}

void Delay(unsigned int num) //@12.000MHz
{
    unsigned char i, j;
    while (num--)
    {
        i = 2;
        j = 239;
        do
        {
            while (--j)
                ;
        } while (--i);
    }
}

void Delay10us(unsigned int num) //@12.000MHz
{
    unsigned char i;
    while (num--)
    {
        _nop_();
        i = 2;
        while (--i)
            ;
    }
}
