#ifndef SPI_H_
#define SPI_H_


#include "stm32f103x6.h"
#include <stdint.h>


void SPI1_CLOCK_EN(void);
void SPI1_PORT_EN(void);
void SPI1_CONFIG(void);

void CR_DISABLE(void);
void CR_ENABLE(void);

void SPI1_SEND_BYTE(uint8_t data);
void SPI1_SEND_STRING(const char *str);

#endif
