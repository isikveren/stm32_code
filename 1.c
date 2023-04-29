#include <stdio.h>

int main()
{
    printf("hello,%d", 7 & ~(1 << 0));
    return 0;
}