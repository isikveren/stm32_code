#ifndef __WS2812_h
#define __WS2812_h
void ws2812_init(void);
void ws2812_rgb(uint8_t ws_i, uint8_t ws_r, uint8_t ws_g, uint8_t ws_b);
void ws2812_refresh(uint8_t ws_i);
void ws2812_reset(void);
void send_res(void);
void send_res(void); // 300us
void delay_250ns(void);
void send_0(void);
void send_1(void);
#endif