#define PERIPH_BASE (0x40000000UL)
#define GPIOA_BASE_OFFSET (0x10800UL)
#define GPIOA_BASE (PERIPH_BASE + GPIOA_BASE_OFFSET)
#define GPIOA_CRL_OFFSET (0x00UL)
#define GPIOA_CRL (*(volatile unsigned int *)(GPIOA_BASE + GPIOA_CRL_OFFSET))

#define RCC_OFFSET (0x21000UL)
#define RCC_BASE (PERIPH_BASE + RCC_OFFSET)
#define RCC_APB2ENR_OFFSET (0x18UL)
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + RCC_APB2ENR_OFFSET))

#define GPIOA_BSRR_OFFSET (0x10UL)
#define GPIOA_BSRR (*(volatile unsigned int *)(GPIOA_BASE + GPIOA_BSRR_OFFSET))

int main() {

  // objective enable pin A0

  // GPIO Bus is APB2
  RCC_APB2ENR |= (1U << 2);

  // reset mode
  GPIOA_CRL &= ~(1U << 0);
  GPIOA_CRL &= ~(1U << 1);
  // set to 2MHz out
  GPIOA_CRL |= (1U << 1);
  // set to gpio push/pull
  GPIOA_CRL &= ~(1U << 2);
  GPIOA_CRL &= ~(1U << 3);

  while (1) {
    // set the pin high (write only)
    GPIOA_BSRR = (1U << 0);
  }
  return 0;
}
