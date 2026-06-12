/*
toggle LED every 5 second using RTC and interupts
 */

#include "stm32f103x6.h"
#include <GPIO.h>
#include <TIM.h>
#include <RTC.h>
#include <stdint.h>


static void RTC_CALLBACK(void);

int main() {

  EnableGPIO13();
  initRTC();

  while (1) {

  }
}

static void RTC_CALLBACK(void){
  if ((GPIOC->ODR & GPIO_ODR_ODR13)){ // if LOW
    GPIOC->BSRR = GPIO_BSRR_BR13; // enable 
  } else {
    GPIOC->BSRR = GPIO_BSRR_BS13; // (disable) active low
  }
}

void RTC_IRQHandler(void){
  if (RTC->CRL & RTC_CRL_SECF){

    while(!(RTC->CRL & RTC_CRL_RTOFF)); // ensure its possible to write to RTC registers
    RTC->CRL &= ~(RTC_CRL_SECF);
    while(!(RTC->CRL & RTC_CRL_RTOFF));
    RTC_CALLBACK();
  }
}
