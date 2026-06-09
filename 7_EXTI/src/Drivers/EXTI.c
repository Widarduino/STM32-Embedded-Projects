#include "EXTI.h"
#include "cmsis_gcc.h"
#include "stm32f103x6.h"

void initEXTI(void){

// detects on pin A2

	__disable_irq();
	// ^ ensures that configuration is not interupted
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	// enable gpio A clock
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//enable AIFO clock ( For the EXTI lines)
	
	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2); // input mode
	GPIOA->CRL |= (GPIO_CRL_CNF2_1); // pull-up/pull-down input
	
	AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI2);
	//routes exti2 to PA2
	
	EXTI->IMR |= EXTI_IMR_MR2; // unmask line 2 interupt
	EXTI->FTSR |= EXTI_FTSR_FT2; // select falling edge 
	EXTI->RTSR &= ~(EXTI_RTSR_RT2); // disable rising edge
	// generate interupt on pin 2
	
	NVIC_EnableIRQ(EXTI2_IRQn);
	// enable EXT in the NVIC

	__enable_irq();
	// must be renabled
}
