/*
 * main.h
 *
 *  Created on: May 26, 2026
 *      Author: hillary
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "spi.h"

#define LED1_PIN 13
#define LED2_PIN 3
#define LED3_PIN 15
#define LED1_GPIO GPIOB
#define LED2_GPIO GPIOA
#define LED3_GPIO GPIOB

#define DISP_CS_PIN 4
#define DISP_DC_PIN 2
#define DISP_RST_PIN 0

#define DISP_CS_GPIO GPIOB
#define DISP_DC_GPIO GPIOB
#define DISP_RST_GPIO GPIOB

#define EXIT_BTN_PIN 10
#define OK_BTN_PIN 11
#define EXIT_BTN_GPIO GPIOB
#define OK_BTN_GPIO GPIOB

#define PRESSED_OK_FLAG (1 << 0)
#define PRESSED_EXIT_FLAG (1 << 1)
#define HOME_FLAG (1 << 2)
#define MENU_FLAG (1 << 3)
#define START_AIRRACE_FLAG (1 << 4)
#define START_APP_FLAG (1 << 5)

void delay_ms(uint32_t ms);

#endif /* MAIN_H_ */
