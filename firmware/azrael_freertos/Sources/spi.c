/*
 * spi.c
 *
 *  Created on: May 26, 2026
 *      Author: hillary
 */

#include "main.h"
#include "stm32f1xx.h"

void spi1_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;    // enable GPIOA clock

	// reset PA4, PA5, PA7 MODE and CNF to 0b00
	GPIOA->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4 | GPIO_CRL_MODE3 | GPIO_CRL_CNF3 |
	                GPIO_CRL_MODE5 | GPIO_CRL_CNF5 |
	                GPIO_CRL_MODE6 | GPIO_CRL_CNF6 |
	                GPIO_CRL_MODE7 | GPIO_CRL_CNF7);

	// init PA5 SCK, PA7 MOSI - Mode = b11 (50Mhz) - CNF = b10 (Alt Function PP)
	GPIOA->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_CNF5_1) |
	              (GPIO_CRL_MODE7 | GPIO_CRL_CNF7_1);

	// init PA6 MISO - Mode = b00 (Input) - CNF = b01 (Floating)
	// GPIOA->CRL &= ~GPIO_CRL_MODE6;
	// GPIOA->CRL &= ~GPIO_CRL_CNF6_1;
	// GPIOA->CRL |= GPIO_CRL_CNF6_0;

	// init PA4 NSS - Mode = b11 (50MHz) - CNF = b00 (General Output PP)
	GPIOA->CRL |= GPIO_CRL_MODE4 | GPIO_CRL_MODE3;

	RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_AFIOEN);    // enable SPI1 clock
	SPI1->CR1  = SPI_CR1_MSTR |                // SPI master mode
	             SPI_CR1_BR_0;                 // bit rate prescale / 4 (72MHz/4 = 18MHz)

	SPI1->CR1 &= ~(SPI_CR1_DFF |               // 8-bit
	               SPI_CR1_LSBFIRST |          // MSB First
	               SPI_CR1_RXONLY);            // Full duplex

	SPI1->CR1 |= (SPI_CR1_SSM |                // Software Slave Management enabled
	              SPI_CR1_SSI);                // Slave Select Internal

}

void spi1_transmit(uint8_t * buf, uint16_t len){
	SPI1->CR1 |= SPI_CR1_SPE;              // Enable SPI1
	GPIOA->BRR |= GPIO_BRR_BR4;             // CS activated (PA4 = LOW)
	for (int i = 0; i<len; i++) {
		while (!(SPI1->SR & SPI_SR_TXE));  // wait till tx buffer is empty
		SPI1->DR = buf[i];             // load a byte to DR register
	}
	while (SPI1->SR & SPI_SR_BSY);

	__IO uint32_t tmpreg_ovr = 0x00U;
	tmpreg_ovr = SPI1->DR;
	tmpreg_ovr = SPI1->SR;
	(void)tmpreg_ovr;
	GPIOA->BSRR |= GPIO_BSRR_BS4;           // CS de-activated (PA4 = HIGH)
	SPI1->CR1 &= ~SPI_CR1_SPE;             // Disable SPI1
}
