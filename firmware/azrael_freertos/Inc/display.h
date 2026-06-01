/*
 * display.h
 *
 *  Created on: Apr 22, 2026
 *      Author: hillary
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "st7735.h"
#include "fonts.h"
#include <string.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 160

typedef enum
{
	TEXT, IMAGE, RECT
} disp_data_type_t;

typedef struct
{
	char buf[50];
	disp_data_type_t data_type;
	uint8_t x_pos;
	int16_t y_pos;
	FontDef *font_size;
	DispColoursDef colour;
	DispColoursDef bg_colour;
	uint8_t w;
	uint8_t h;
	const uint16_t *data;
	uint16_t transparent_color;
} displayData_t;

void display_init();
void display_print_str(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color);
void display_print_str_bg(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void display_DrawImageTransparent(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data, uint16_t transparent_color);
void display_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

#endif /* INC_DISPLAY_H_ */
