#include "RTC.h"
#include "stm32f103x6.h"

void initRTC(void){
	
	__disable_irq();
	RCC->APB1ENR |= RCC_APB1ENR_PWREN; 
	// enable PWR clk
	// important for allowing rtc clock config
	
	RCC->APB1ENR |= RCC_APB1ENR_BKPEN; // enable bkp clk
	
	PWR->CR |= PWR_CR_DBP; // disable backup domain protection
	
	RCC->BDCR |= RCC_BDCR_BDRST; // resets the clock
	RCC->BDCR &= ~(RCC_BDCR_BDRST);
	
	RCC->BDCR |= RCC_BDCR_LSEON; // enable LSE oscillator
	while (!(RCC->BDCR & RCC_BDCR_LSERDY)){} //poll while LSE turns on

	RCC->BDCR &= ~(RCC_BDCR_RTCSEL); // reset register
	RCC->BDCR |= RCC_BDCR_RTCSEL_LSE; // use LSE as RTC clock
	
	

	RCC->BDCR |= RCC_BDCR_RTCEN; // enable RTC Clock
	RTC->CRL &= ~(RTC_CRL_RSF);
	while(!(RTC->CRL & RTC_CRL_RSF)){} // wait for synchro
	
	while (!(RTC->CRL & RTC_CRL_RTOFF)){} // poll the RT until its ready
	RTC->CRL |= RTC_CRL_CNF; // enter config mode
	
	// this sets the reload point to 5s
	RTC->PRLH = 0x0002;
	RTC->PRLL = 0x7FFF;
	// RTC->CRL &= ~(RTC_CRL_SECF)
	// the DIV register shows progress towards PRLL
	
	RTC->CRL &= ~(RTC_CRL_CNF); // exit config mode
	while (!(RTC->CRL & RTC_CRL_RTOFF)){} // poll the RT until its ready
	

	RTC->CRL &= ~(RTC_CRL_SECF); // reset interupt flag incase
	RTC->CRH |= RTC_CRH_SECIE; // second interupt enabled
	while (!(RTC->CRL & RTC_CRL_RTOFF)){} // poll the RT until its ready

	NVIC_EnableIRQ(RTC_IRQn);

	__enable_irq();

}
