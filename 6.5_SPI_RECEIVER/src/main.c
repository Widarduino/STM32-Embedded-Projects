/*
 29/05/2026
 This code will send and receive data to another stm32 via SPI and then the
 received data via uart to be monitored via serial
 */

#include "stm32f103x6.h"
#include <GPIO.h>
#include <SPI.h>
#include <TIM.h>
#include <UART.h>
#include <stdint.h>

// Receiver Microcontroller

int main() {

  EnableGPIO13();
  Enable_1S_TIMER();

  uart_enable();
  SPI1_Enable();

  DEBUG_LED_ON();
  delayS(3);
  DEBUG_LED_OFF();
  delayS(1);

  uint8_t buffer[4] = {'N', 'U', 'L', 'L'};

  while (1) {

    if (!(GPIOA->IDR & GPIO_IDR_IDR1)) {
      DEBUG_LED_ON(); // when pulled low by master

      SPI1_RECEIVE_STRING(buffer, 4); // write 4 bytes into buffer

      for (int i = 0; i < 4; i++) {
        uart_write(buffer[i]); // write via uart (TX:pin A2)
      }

    } else {
      DEBUG_LED_OFF();
    }
  }
}
