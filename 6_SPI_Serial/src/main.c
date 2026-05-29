/*
 29/05/2026
 SPI driver to read and write to serial and eventually some type of device
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

  DEBUG_LED_ON();
  delayS(10);
  DEBUG_LED_OFF();

  while (1) {
    // baudrate is currently at 500kHz
    SPI1_SEND('t');
  }
}
