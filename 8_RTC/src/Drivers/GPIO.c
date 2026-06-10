#include "GPIO.h"

void EnableGPIO13(void) {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // enable clock to pereipheral
  GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13); // enable pin mode/state
  GPIOC->CRH |= GPIO_CRH_MODE13_1;
}

void DEBUG_LED_ON(void) {
  GPIOC->BSRR = GPIO_BSRR_BR13; // enable
}
void DEBUG_LED_OFF(void) {
  GPIOC->BSRR = GPIO_BSRR_BS13; // disable (active low)
}

