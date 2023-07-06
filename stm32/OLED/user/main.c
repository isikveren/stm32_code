#include "stm32f10x.h"
#include "OLED.h"

int main()
{
    OLED_Init();

    OLED_ShowString(1, 1, "hello");
    while (1)
    {

        /* code */
    }
}
