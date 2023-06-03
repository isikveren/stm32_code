
#include "debug.h"
#include "system.h"
// #include "OLED.h"ÄãºÃ

int main(void)
{
    System_Init();
    while (1)
    {
        System_Loop();
    }
}
