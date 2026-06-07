#include "SPI.h"
#include "stm32f103x6.h"
#include <stdint.h>

void SPI1_CLOCK_EN(void) { RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN);}

void SPI1_PORT_EN(void) {
  GPIOA->CRL &= ~(
                 GPIO_CRL_CNF5 | GPIO_CRL_MODE5
                | GPIO_CRL_CNF6 | GPIO_CRL_MODE6 
                | GPIO_CRL_CNF7 | GPIO_CRL_MODE7
                | GPIO_CRL_CNF2 | GPIO_CRL_MODE2
  ); // reset all registers

  // Datasheet page 167
  // PA4 = nss PA5 = sck PA6 = miso PA7 = mosi

  // CLK (SPI_Master_Clock_EN)
  GPIOA->CRL |= (GPIO_CRL_MODE5_0    // output mode 10Mhz
                 | GPIO_CRL_CNF5_1   // alternate push-pull
                                     // MOSI (SPI_FULL_DUPLEX_MASTER)
                 | GPIO_CRL_MODE7_0  // output mode 10Mhz
                 | GPIO_CRL_CNF7_1   // alternate push-pull
                                     // MISO (SPI_FULL_DUPLEX_MASTER)
                 | GPIO_CRL_CNF6_0   // input mode floating input
                ); // nss is not used so not configured
  
  // CR pin (A2)
  GPIOA->CRL |= (GPIO_CRL_MODE2_0); // 10Mhz  general push-pull

}

void CR_ENABLE(void){
   GPIOA->BSRR = GPIO_BSRR_BR2; // ( pulls low)
}

void CR_DISABLE(void){
  GPIOA->BSRR = GPIO_BSRR_BS2; // (pulls high)
}

void SPI1_CONFIG(void) {

  // Datasheet page 742
  SPI1->CR1 &= ~(SPI_CR1_BIDIMODE // full duplex
                 | SPI_CR1_CRCEN  // CRC Calculation disabled
                 | SPI_CR1_RXONLY // disable receive only (full duplex)
                 | SPI_CR1_DFF    // 8 bit data transactions
                 | SPI_CR1_BR // reset field
                 | SPI_CR1_CPOL | SPI_CR1_CPHA // reset field
  );


  SPI1->CR1 |= (SPI_CR1_LSBFIRST // LSB first
                | SPI_CR1_BR_1   //  set baud rate to 8Mhz / 128 = 62500hz
                | SPI_CR1_BR_2   //
                | SPI_CR1_MSTR //  enable master mode
                | SPI_CR1_SSM                 // Software controlled NSS
                | SPI_CR1_SSI // internal slave select
                | SPI_CR1_CPOL | SPI_CR1_CPHA // SPI MODE_3
  );

  SPI1->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE | SPI_CR2_ERRIE |
                 SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
  // disable all interupts flags

  SPI1->CR1 &= ~(SPI_CR1_SPE); // clear
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
  CR_ENABLE();
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
  CR_DISABLE();
}


