#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include "main.h"
#include "gpio.h"


void gpio_init(void)
{
   // Enable clocks for GPIOA, GPIOB, AFIO
   RCC->APB2ENR |= RCC_APB2ENR_IOPAEN   // GPIOA
                |  RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;  // GPIOB and AFIO

    // PB15 - LED_3 - output push-pull
    // PB13 - LED_1 - output push-pull
    // PA3  - LED_2 - output push-pull
    // PB0  - DISP_RST - output push-pull
    // PB2  - DISP_DC  - output push-pull

   // Clear bits PB0, PB2
   GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0 | GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
    
   // clear bits PA3
   GPIOA->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_MODE3);

   // clear bits PB13, PB15
    GPIOB->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13 | GPIO_CRH_CNF15 | GPIO_CRH_MODE15);
    
    // Set PB0, PB2 as output push-pull, max speed 50 MHz
    GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE2;

    // Set PA3 as output push-pull, max speed 50 MHz
    GPIOA->CRL |= GPIO_CRL_MODE3;

    // Set PB13, PB15 as output push-pull, max speed 50 MHz
    GPIOB->CRH |= GPIO_CRH_MODE13 | GPIO_CRH_MODE15;

    // PB11 - OK_BTN - input with pull-up
    // PB10 - EXIT_BTN - input with pull-up
    GPIOB->CRH &= ~(GPIO_CRH_CNF11 | GPIO_CRH_MODE11 | GPIO_CRH_CNF10 | GPIO_CRH_MODE10);
    GPIOB->CRH |= GPIO_CRH_CNF11_1 | GPIO_CRH_CNF10_1; // Input with pull-up/pull-down
    GPIOB->ODR |= (1 << OK_BTN_PIN) | (1 << EXIT_BTN_PIN); // Enable pull-up

    // Configure EXTI for PB11 and PB10
    AFIO->EXTICR[2] &= ~(AFIO_EXTICR3_EXTI11 | AFIO_EXTICR3_EXTI10); // Clear EXTI11 and EXTI10 bits

    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI11_PB | AFIO_EXTICR3_EXTI10_PB; // Map EXTI11 and EXTI10 to PB

    // unmask EXTI11 and EXTI10
    EXTI->IMR |= (1 << 11) | (1 << 10);

    // Trigger on falling edge for both buttons
    EXTI->RTSR &= ~((1 << 11) | (1 << 10)); // Disable rising edge trigger
    EXTI->FTSR |= (1 << 11) | (1 << 10);  // Enable falling edge trigger

    // Enable EXTI15_10_IRQn for PB11 and PB10
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_SetPriority(EXTI15_10_IRQn, 6);
}

void gpio_disp_dc_high(void)
{
	DISP_DC_GPIO->BSRR = (1U << DISP_DC_PIN);
}
void gpio_disp_dc_low(void)
{
	DISP_DC_GPIO->BRR = (1U << DISP_DC_PIN);
}
void gpio_disp_rst_high(void)
{
	DISP_RST_GPIO->BSRR = (1U << DISP_RST_PIN);
}
void gpio_disp_rst_low(void)
{
	DISP_RST_GPIO->BRR = (1U << DISP_RST_PIN);
}

extern EventGroupHandle_t xSystemFlags;
/** Button Interrupt Handler */
void EXTI15_10_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Check if EXTI11 (OK button) triggered the interrupt
    if (EXTI->PR & (1 << OK_BTN_PIN))
    {
        LED1_GPIO->BSRR |= (1 << LED1_PIN);
        xEventGroupSetBitsFromISR(xSystemFlags, PRESSED_OK_FLAG, &xHigherPriorityTaskWoken);
        EXTI->PR |= (1 << OK_BTN_PIN); // Clear the pending bit by writing 1
        // Handle OK button press here
    }

    // Check if EXTI10 (EXIT button) triggered the interrupt
    if (EXTI->PR & (1 << EXIT_BTN_PIN))
    {
        LED1_GPIO->BRR |= (1 << LED1_PIN);
        xEventGroupSetBitsFromISR(xSystemFlags, PRESSED_EXIT_FLAG, &xHigherPriorityTaskWoken);
        EXTI->PR |= (1 << EXIT_BTN_PIN); // Clear the pending bit by writing 1
        // Handle EXIT button press here
    }

    // If a higher priority task was woken, request a context switch
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

