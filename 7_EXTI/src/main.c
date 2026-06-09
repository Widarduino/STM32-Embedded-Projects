// 7/07/2026


// this uses interupts rather than polling for the button press
#include "stm32f103x6.h"
#include <GPIO.h>
#include <EXTI.h>
#include <TIM.h>
#include <stdint.h>


int main() {

  EnableGPIO13();
  Enable_1S_TIMER();

  DEBUG_LED_ON();
  delayS(2);
  DEBUG_LED_OFF();
  delayS(2);

  initEXTI();


  while (1) {

  }
}

static void exti2_callback(){
  if ((GPIOC->ODR & GPIO_ODR_ODR13)){ // if LOW
    GPIOC->BSRR = GPIO_BSRR_BR13; // enable 
  } else {
    GPIOC->BSRR = GPIO_BSRR_BS13; // (disable) active low
  }
}

void EXTI2_IRQHandler(void){
  if ((EXTI->PR & EXTI_PR_PR2) != 0){
    // if pending
    EXTI->PR |= EXTI_PR_PR2;
    // clear pending bit
    exti2_callback();
  } }
