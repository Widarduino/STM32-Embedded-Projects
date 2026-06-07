#ifndef TIM_H_
#define TIM_H_

#include "stm32f103x6.h"
#include <stdint.h>


void Enable_1S_TIMER() {
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  TIM1->PSC = 1600 - 1;
  TIM1->ARR = 5000 - 1;
  TIM1->CNT = 0;
  TIM1->CR1 = TIM_CR1_CEN;
}

void delayS(int cycles){
  for (int i = 0; i < cycles; i++) {
    while (!(TIM1->SR & TIM_SR_UIF)) { } // while both are zero hold for 1ms
    TIM1->SR &= ~TIM_SR_UIF; // reset the bit
  }
}
#endif
