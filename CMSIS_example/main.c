#include "stm32f103x6.h"

int main() {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
  GPIOC->CRH |= GPIO_CRH_MODE13_1;

  while (1) {
    GPIOC->BSRR = GPIO_BSRR_BR13;
  }
}
