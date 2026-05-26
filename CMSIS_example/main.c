/* 
 this CMSIS libraries introduce a standardization to all ARM microcontrollers and 
 how registers are defined to make code more readable and organized. this is functionally
 the same as REGISTERMANIP however it uses CMSIS libs rather than manually bitmasking
 registers
 */



#include "stm32f103x6.h"

int main() {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
  GPIOC->CRH |= GPIO_CRH_MODE13_1;

  while (1) {
    GPIOC->BSRR = GPIO_BSRR_BR13;
  }
}
