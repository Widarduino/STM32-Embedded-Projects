#include "SysTick.h"
#include "stm32f103x6.h"

#define CTRL_CLKEN (1U << 0)
#define CTRL_CLKSRC (1U << 2)
#define CTRL_CLKSTAT (1U << 16)
#define DEFAULT_CLK_MS 8000

// clock defaults to 8Mhz

void systick_msec_delay(uint32_t delay) {
  // load cycles and default expression for 1 ms
  SysTick->LOAD = DEFAULT_CLK_MS - 1;
  SysTick->VAL = 0;

  // load ctrl (internal)
  SysTick->CTRL |= CTRL_CLKSRC;
  // enable clock
  SysTick->CTRL |= CTRL_CLKEN;

  for (int i = 0; i < delay; i++) {
    while ((SysTick->CTRL & CTRL_CLKSTAT) == 0) {
    }
  }

  // disable clk
  SysTick->CTRL = 0;
}

int main() {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
  GPIOC->CRH |= GPIO_CRH_MODE13_1;

  while (1) {
    GPIOC->BSRR = GPIO_BSRR_BR13;
    systick_msec_delay(1000);
    GPIOC->BSRR = GPIO_BSRR_BS13;
    systick_msec_delay(1000);
  }
}
