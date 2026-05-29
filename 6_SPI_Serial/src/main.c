/*
 26/05/2026
 this is the basic function of a UART driver that will serially transmit uart
 data to be read by an arduino as I do not current have any other way to read
 the data directly.
 */

#include "GPIO.h"
#include "TIM.h"
#include "UART.h"

void delayS(int cycles);

int main() {

  EnableGPIO13();
  Enable_1S_TIMER();

  DEBUG_LED_ON();
  delayS(5); // delays to allow arduino to initialize itself
  DEBUG_LED_OFF();

  uart_enable();
  while (1) {
    uart_send_str("this is a test\n");
  }
}

void delayS(int cycles) {
  for (int i = 0; i < cycles; i++) {
    while (!(TIM1->SR & TIM_SR_UIF)) { } // while both are zero hold for 1ms
    TIM1->SR &= ~TIM_SR_UIF; // reset the bit
  }
}
