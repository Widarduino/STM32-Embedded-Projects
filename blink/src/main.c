#define STM32F10X_MD // inidicates chip density (datasheet)
#include "stm32f10x.h" // header defines the variables used in the main code 
                       // these are structures mapped to harware registers

void delay(volatile uint32_t t) // volatile prevents compiler from optimizing
{
    while(t--); // keeps cpu busy
}

int main(void)
{
    /* Enable GPIOC clock 'IO port c enable' */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 
    /* 
    reset control clock (RCC)
    APB2ENR (APB2 Enable register)
    IOPCEN (io port c enable)
    for the stm32 the clock must be clocked before use
    */

    /* Configure PC13 as Push-Pull Output, 2 MHz */
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13); // clear bits ( review bitwise operations)
    /*
    CRH (configure register high pins 8-15) where each pin control 4 bits for the modes
    CNF(1:0)
    MODE(1:0) meaning that pin 13 has bits 23..20 
    we clear MODE and CNF bits using bitwise operations

    so gpio register i [00 00]
                       CRN CNF
    */
    GPIOC->CRH |= GPIO_CRH_MODE13_1;
    /* we just set the mode to output at 2MHz speed because mode is 10
     we bitwise change MSB of mode 1 to enable
         [00 10]
         CRN CNF
    GPIOC->CRH |= GPIO_CRH_MODE13_0 (what this would have done is...)
         [00 01]
         CRN CNF
    page 172 reference manual
      */

    while(1)
    {
        //GPIOC->ODR ^= GPIO_ODR_ODR13;  // toggle LED
        /* output data register (XOR comparasion)*/
        //delay(800000);

        GPIOC->BRR = GPIO_BRR_BR13;
        // reset registor (pin 13)
    }
}

/* IMPORTANT FLASH COMMAND using OpenOCD (one line)
 * openocd 
 * \ -f interface/stlink.cfg  (loads stlink config(usb protocal , SWD interface clock speed))
 * \ -f target/stm32f1x.cfg  (loads chip config(flash layout, CPU type, memory map, reset behavior))
 * \ -c "program blink.elf verify reset exit" (openOCD comands using -c flag)
*/
// debuging flash
//openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program blink.elf verify reset exit"
// st-flash write blink.bin 0x08000000 (quick flash)
