/*
 * display.c
 *
 *  Created on: Apr 22, 2026
 *      Author: hillary
 */

#include "display.h"

//volatile uint16_t disp_buff[ST7735_WIDTH][ST7735_HEIGHT];

void display_init() {
    ST7735_Init();
}

void display_print_str(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color){
	ST7735_WriteStringTransparent(x, y, str, font, color);
}

void display_print_str_bg(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor){
	ST7735_WriteString(x, y, str, font, color, bgcolor);
}

void display_DrawImageTransparent(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data, uint16_t transparent_color){
	ST7735_DrawImageTransparent(x, y, w, h, data, transparent_color);
}

void display_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
	ST7735_FillRectangle(x, y, w, h, color);
}
