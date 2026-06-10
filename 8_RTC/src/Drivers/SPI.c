#include "SPI.h"
#include "stm32f103x6.h"
#include <stdint.h>

void SPI1_CLOCK_EN(void) {
  RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN);
}

void SPI1_PORT_EN(void) {
  GPIOA->CRL &=
      ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5 |
        GPIO_CRL_CNF6 | GPIO_CRL_MODE6 | 
        GPIO_CRL_CNF7 | GPIO_CRL_MODE7 |
        GPIO_CRL_CNF1 | GPIO_CRL_MODE1
       ); // reset all registers

  // Datasheet page 167
  // PA4 = nss PA5 = sck PA6 = miso PA7 = mosi

  // CLK (SPI_Master_Clock_EN)
  GPIOA->CRL |= (
                   GPIO_CRL_CNF5_0   // input floating
                                     // MOSI (SPI_FULL_DUPLEX_SLAVE)
                 | GPIO_CRL_CNF7_1   // input pull/pull
                                     // MISO (SPI_FULL_DUPLEX_SLAVE)
                 | GPIO_CRL_MODE6_0 // 10Mhz
                 | GPIO_CRL_CNF6_1   // alternate push/pull
                 ); 

  // CR pin (A1) ( RECEIVER )
  GPIOA->CRL |= (GPIO_CRL_CNF1_1); // internal pull-pull/pull down input
}

void SPI1_CONFIG(void) {

  // Datasheet page 742
  SPI1->CR1 &= ~(SPI_CR1_BIDIMODE // full duplex
                 | SPI_CR1_BIDIOE // receive only
                 | SPI_CR1_CRCEN  // CRC Calculation disabled
                 | SPI_CR1_DFF   // 8 bit data transactions
                 | SPI_CR1_MSTR //  slave configuration
  );
// revonfigure this properly later for slave mode, only the master controls the gpio
  SPI1->CR1 |= (SPI_CR1_LSBFIRST // LSB first
              | SPI_CR1_CPOL | SPI_CR1_CPHA // SPI MODE_3
  );

  SPI1->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE | SPI_CR2_ERRIE |
                 SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
  // disable all interupts flags


  SPI1->CR1 |= (SPI_CR1_SPE); //  enable SPI
}

void SPI1_SEND_BYTE(uint8_t data) {
  // this is a 1 byte write only command
  while (!(SPI1->SR & (SPI_SR_TXE))) {
  } // wait until buffer is empty
  SPI1->DR = data; // write data
}

void SPI1_SEND_STRING(const char *str) {
  uint8_t temp;

  while (*str) {
    SPI1_SEND_BYTE(*str++);
  }

  while (!(SPI1->SR & (SPI_SR_TXE))) {
  } // wait until buffer is empty
  while (SPI1->SR & (SPI_SR_BSY)) {
  } // ensures spi is not busy

  temp = SPI1->DR; // after sending data via the DR the slave sends it back via
  temp = SPI1->SR; // reading these resgisters clears the OVR flag (data not
                   // read in time)
}

void SPI1_RECEIVE_BYTE(uint8_t *buffer) {
 // SPI1->DR = 0; // not needed for receiver
  while (!(SPI1->SR & (SPI_SR_RXNE))) {
  } // ensures spi is not busy
  *buffer = (SPI1->DR); // reads for a byte
}

void SPI1_RECEIVE_STRING(uint8_t *buffer, uint32_t size) {

  while (size) {
    SPI1_RECEIVE_BYTE(buffer);
    buffer++;
    size--;
  }
}

void SPI1_Enable() {
  SPI1_CLOCK_EN();
  SPI1_PORT_EN();
  SPI1_CONFIG();
}
