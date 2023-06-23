
#ifndef __MYSPI_H
#define __MYSPI_H
#include "ch32f10x.h"

void MySPI_Init(void);
void MySPI_W_SS(uint8_t BitValue);
void MySPI_W_SCK(uint8_t BitValue);
uint8_t MySPI_W_MISO(void);
void MySPI_W_MOSI(uint8_t BitValue);
void MySPI_W_RES(uint8_t BitValue);
void MySPI_W_DC(uint8_t BitValue);
void MySPI_Start(void);

void MySPI_Stop(void);

uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif
