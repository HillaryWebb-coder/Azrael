#ifndef SPI_H_
#define SPI_H_

#include "stm32f1xx.h"

void spi1_init(void);
void spi1_transmit(uint8_t * buf, uint16_t len);

#endif /* SPI_H_ */