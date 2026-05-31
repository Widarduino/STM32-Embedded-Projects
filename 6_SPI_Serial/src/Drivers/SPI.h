#ifndef SPI_H_
#define SPI_H_


#include "stm32f103x6.h"
#include <stdint.h>


void SPI1_CLOCK_EN(void);
void SPI1_PORT_EN(void);
void SPI1_CONFIG(void);

void SPI1_SEND_BYTE(uint8_t data);

void SPI1_RECEIVE_BYTE(uint8_t *buffer);

#endif
