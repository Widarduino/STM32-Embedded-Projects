#include "SPI.h"
#include "stm32f103x6.h"
#include <stdint.h>

void SPI1_CLOCK_EN(void) { RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; }

void SPI1_PORT_EN(void) {
  GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4 | GPIO_CRL_CNF5 |
                  GPIO_CRL_MODE5 | GPIO_CRL_CNF6 | GPIO_CRL_MODE6 |
                  GPIO_CRL_CNF7 | GPIO_CRL_MODE7); // reset all registers

 // Datasheet page 125
// PA4 = nss PA5 = sck PA6 = miso PA7 = mosi

// CLK (SPI_Master_Clock_EN)
  GPIOA->CRL |= (GPIO_CRL_MODE5_0    // output mode 10Mhz
                 | GPIO_CRL_CNF5_1   // alternate push-pull
// MOSI (SPI_FULL_DUPLEX_MASTER)
                 | GPIO_CRL_MODE7_0  // output mode 10Mhz
                 | GPIO_CRL_CNF7_1   // alternate push-pull
// MISO (SPI_FULL_DUPLEX_MASTER)
                 | GPIO_CRL_CNF6_0   // input mode floating input
// NSS (SPI_HARDWARE_MASTER/SLAVE)
                 | GPIO_CRL_CNF4_0); // input mode floating input

}

void SPI1_CONFIG(void) {

  // Datasheet page 742
  SPI1->CR1 &= ~(SPI_CR1_BIDIMODE // full duplex
                 | SPI_CR1_CRCEN  // CRC Calculation disabled
                 | SPI_CR1_RXONLY // disable receive only (full duplex)
                 | SPI_CR1_SSM    // NSS hardware management
                 | SPI_CR1_DFF    // 8 bit data transactions
  );

  SPI1->CR1 |= (SPI_CR1_LSBFIRST // LSB first
                | SPI_CR1_BR_1   //  set baud rate to 8Mhz / 16 = 500Khz
                | SPI_CR1_BR_0 | SPI_CR1_MSTR //  enable master mode
                | SPI_CR1_CPOL                //  CK idle at 1
                | SPI_CR1_CPHA // second transition is first data capture edge
  );

  SPI1->CR2 &=
      ~(SPI_CR2_TXEIE // disable all interupts flags
        | SPI_CR2_RXNEIE | SPI_CR2_ERRIE | SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);

  SPI1->CR2 |= (SPI_CR2_SSOE // NSS is pulled low when spi is enabled (single
                             // slave/master config)
  );

  SPI1->CR1 |= (SPI_CR1_SPE); //  enable SPI
}

void SPI1_SEND(uint8_t data) {
  while (!(SPI1->SR & SPI_SR_TXE)) {
  }
  SPI1->DR = data;
}
