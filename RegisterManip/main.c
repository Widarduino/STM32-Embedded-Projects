#define PERIPH_BASE (0x40000000UL)
#define GPIOC_BASE_OFFSET (0x11000UL)
#define GPIOC_BASE (PERIPH_BASE + GPIOC_BASE_OFFSET)
#define GPIOC_CRH_OFFSET (0x04UL)
#define GPIOC_CRH (*(volatile unsigned int *)(GPIOC_BASE + GPIOC_CRH_OFFSET))

#define RCC_OFFSET (0x21000UL)
#define RCC_BASE (PERIPH_BASE + RCC_OFFSET)
#define RCC_APB2ENR_OFFSET (0x18UL)
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + RCC_APB2ENR_OFFSET))

#define GPIOC_BSRR_OFFSET (0x10UL)
#define GPIOC_BSRR (*(volatile unsigned int *)(GPIOC_BASE + GPIOC_BSRR_OFFSET))

int main() {

  // objective enable pin C13

  // GPIO Bus is APB2
  RCC_APB2ENR |= (1U << 4);
// set the bit for IOPCEN
  // reset all registers
  GPIOC_CRH &= ~(1U << 20); //mode 20
  GPIOC_CRH &= ~(1U << 21); //mode 21
  GPIOC_CRH &= ~(1U << 22); //CNF 22
  GPIOC_CRH &= ~(1U << 23); //CNF 23
  // set to 2MHz out
  GPIOC_CRH |= (1U << 21); // MODE 21

  while (1) {
    // set the pin high (write only)
    GPIOC_BSRR = (1U << 29);
  }
  return 0;
}
