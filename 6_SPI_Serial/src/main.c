/*
 29/05/2026
 This code will send and receive data to another stm32 via SPI and then the
 received data via uart to be monitored via serial
 */

#include <GPIO.h>
#include <SPI.h>
#include <TIM.h>

int main() {
  EnableGPIO13();
  Enable_1S_TIMER();

  SPI1_CLOCK_EN();
  SPI1_PORT_EN();
  SPI1_CONFIG();
  
  CR_DISABLE(); // pulls high

  DEBUG_LED_ON();
  delayS(10);
  DEBUG_LED_OFF();

  while (1) {
    // baudrate is currently at 500kHz
    SPI1_SEND_STRING("okay");
  }
}
