#include "RTC.h"
#include "stm32f103x6.h"

void initRTC(void){
	
	RCC->APB1ENR |= RCC_APB1ENR_PWREN; 
	// enable PWR clk
	// important for allowing rtc clock config
	
	RCC->APB1ENR |= RCC_APB1ENR_BKPEN; // enable bkp clk
	
	PWR->CR |= PWR_CR_DBP; // disable backup domain protection
	
	
	RCC->CSR |= RCC_CSR_LSION; // enable LSI
	while (!(RCC->CSR & RCC_CSR_LSION)){} //poll while LSI turns on

	RCC->BDCR &= ~(RCC_BDCR_RTCSEL_1 | RCC_BDCR_RTCSEL_0 ); // reset register
	RCC->BDCR |= RCC_BDCR_RTCSEL_1; // use LSI as RTC clock
	
	RCC->BDCR |= RCC_BDCR_RTCEN; // enable RTC Clock
	
	while (!(RTC->CRL & RTC_CRL_RTOFF)){} // poll the RT until its ready
	RTC->CRL |= RTC_CRL_CNF; // enter config mode

	RTC->CRL &= ~(RTC_CRL_CNF); // exit config mode
	

}
