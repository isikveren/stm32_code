#include "stm32f10x.h"
#include "delay.h"

uint8_t ws_data[200][3] = {{0x23, 0x23, 0x12}, {0x00, 0x12, 0x00}, {0x00, 0x21, 0x00}, {0x00, 0x03, 0x00}};

#define PA10(x) GPIO_WriteBit(GPIOA, GPIO_Pin_10, (BitAction)(x))

void ws2812_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //   GPIO_ResetBits(GPIOA, GPIO_Pin_10);
}

void ws2812_rgb(uint8_t ws_i, uint8_t ws_r, uint8_t ws_g, uint8_t ws_b)
{
    ws_data[ws_i - 1][0] = ws_g;
    ws_data[ws_i - 1][1] = ws_r;
    ws_data[ws_i - 1][2] = ws_b;
}

void ws2812_reset(void)
{
    uint8_t i;
    for (i = 1; i <= 200; i++)
    {
        ws2812_rgb(i, 0, 0, 0);
    }
}

void delay_250ns(void)
{
    uint8_t del_t = 3;
    while (del_t--)
    {
        __NOP();
    }
}

void send_res(void) // 300us
{
    PA10(0);
    Delay_us(300);
}

void send_0(void)
{
    PA10(1);
    delay_250ns();
    PA10(0);
    delay_250ns();
    delay_250ns();
    delay_250ns();
}

void send_1(void)
{
    PA10(1);
    delay_250ns();
    delay_250ns();
    delay_250ns();
    PA10(0);
    delay_250ns();
}

// 发送数据
//  1000 0000
void ws2812_refresh(uint8_t ws_i)
{
    uint8_t i = 0, j = 0, ws_ri = 0;
    for (; ws_ri < ws_i; ws_ri++)
    {
        for (; i < 3; i++)
        {
            for (; j < 8; j++)
            {
                if (ws_data[ws_ri][i] & (0x80 >> j) == 0)
                {
                    send_0();
                }
                else
                {
                    send_1();
                }
            }
        }
    }
    send_res();
}
