
#include "debug.h"
#include "system.h"
// #include "OLED.h"���

int main(void)
{
    System_Init();
    while (1)
    {
        System_Loop();
    }
}
