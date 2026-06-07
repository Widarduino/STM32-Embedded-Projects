#ifndef UART_H_
#define UART_H_

#define System_Freq 8000000
#define BaudRate 9600

#include "stm32f103x6.h"
#include <stdint.h>

void uart_enable(void);
uint16_t calculate_BRR(uint32_t desired_baud, uint32_t fclk);
void uart_send_str(const char *str);
void uart_write(uint8_t data);

void uart_enable(void) {
  
  RCC->CFGR &= ~(RCC_CFGR_PPRE1); // prescaler divides by 1 so defaults to 8Mhz

  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;              // enable GPIOA
  RCC->APB1ENR |= (RCC_APB1ENR_USART2EN); // enable USART clock

  GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2); // resets both
  GPIOA->CRL |= (GPIO_CRL_MODE2_0);                // sets to output mode 10Mhz
  GPIOA->CRL |= (GPIO_CRL_CNF2_1);        // sets to alternate mode push-pull

 // USART2->BRR = calculate_BRR(BaudRate, System_Freq); // sets baud rate
  USART2->BRR = 0x341; // manually setting for debugging
  
  USART2->CR1 &= ~(USART_CR1_M | USART_CR1_PCE); // 1 start , 8 data no parity
  USART2->CR1 |= USART_CR1_TE;                     // transfer direction
  USART2->CR1 |= USART_CR1_UE;                     // enable module
}

// the uint is for typesafety as BRR is only 16 bits long
uint16_t calculate_BRR(uint32_t desired_baud, uint32_t fclk) {
  uint32_t divisor = desired_baud * 16;
  uint16_t div = (fclk + (divisor / 2U)) / divisor;
  return div;
}

void uart_send_str(const char *str) {
  while (*str) {
    uart_write(*str++);
  }
}

void uart_write(uint8_t data) {
  while (!(USART2->SR & USART_SR_TXE)) {}// wait while uart data register is not empty
  USART2->DR = data;
}

#endif
