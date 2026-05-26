/* 
 The TIMER peripherals are more desirable for precise delays, measurement
 PWM generation and I/O capture from sensors. As opposed to Systick this is limited
 to the chips onboard peripherals. The timer precision is attributed to the fact that 
 the original clock can undergo several stages of prescaling to enable granular control over the
 periphal
 */


#include "TIM.h"
#include "stm32f103x6.h"

// clock defaults to 8Mhz
// make sure to watch bitwise operations to not overwrite something

void tim_msec_delay() {
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  TIM1->PSC = 1600 - 1;
  TIM1->ARR = 500 - 1;
  TIM1->CNT = 0;
  TIM1->CR1 = TIM_CR1_CEN;
}

void EnableGPIO13() {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // enable clock to pereipheral
  GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13); // enable pin mode/state
  GPIOC->CRH |= GPIO_CRH_MODE13_1;
}

int main() {
  EnableGPIO13();
  tim_msec_delay();
  while (1) {

    GPIOC->BSRR = GPIO_BSRR_BS13; // disable (active low)
    //
    while (!(TIM1->SR & TIM_SR_UIF)) { }     // while both are zero hold
    TIM1->SR &= ~TIM_SR_UIF; // reset the bit

    GPIOC->BSRR = GPIO_BSRR_BR13; // enable

    while (!(TIM1->SR & TIM_SR_UIF)) { }     // while both are zero hold
    TIM1->SR &= ~TIM_SR_UIF; // reset the bit
  }
}

// chip is either remaining on or timer is inperceptible
