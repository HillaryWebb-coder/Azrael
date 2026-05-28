#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f1xx.h"

void gpio_init(void);
void gpio_disp_dc_high(void);
void gpio_disp_dc_low(void);
void gpio_disp_rst_high(void);
void gpio_disp_rst_low(void);

#endif /* GPIO_H_ */