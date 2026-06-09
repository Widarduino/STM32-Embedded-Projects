// 7/07/2026

#include "stm32f103x6.h"
#include <GPIO.h>
#include <EXTI.h>
#include <TIM.h>
#include <stdint.h>


int main() {

  EnableGPIO13();
  Enable_1S_TIMER();

  DEBUG_LED_ON();
  delayS(3);
  DEBUG_LED_OFF();
  delayS(1);

  initEXTI();


  while (1) {

  }
}

static void exti2_callback(){

}

void EXTI2_IRQHandler(void){
  if ((EXTI->PR & EXTI_PR_PR2) != 0){

    EXTI->PR |= EXTI_PR_PR2;

    exti2_callback();
  } }
