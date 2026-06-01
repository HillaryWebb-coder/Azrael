/*
 * airRace.h
 *
 *  Created on: May 3, 2026
 *      Author: hillary
 */

#ifndef INC_AIRRACE_H_
#define INC_AIRRACE_H_

#include "display.h"
#include "assets.h"
#include "lis3dh.h"
//#include "cmsis_os.h"

#define CTRL_SPEED 1
#define DISP_DIV 4
#define OBSTACLE_SPEED OBSTACLE_HEIGHT
#define OBSTACLES_NO 1

#define FIGHTER_Y 140

typedef struct {
	uint8_t current_x;
	const uint16_t *fighter_img;
} Fighter_Typedef;

typedef struct {
	uint8_t current_x;
	int16_t current_y;
	const uint16_t *obstacle_img;
} Obstacle_Typedef;

typedef struct {
	uint8_t x_pos;
	int16_t y_pos;
	uint8_t obs_id;
} ObstaclePos_T;

extern uint8_t refresh_screen;
#define REFRESH refresh_screen

//extern osEventFlagsId_t SystemFlagsHandle;

void init_game(Obstacle_Typedef *obs, Fighter_Typedef *fighter);
uint8_t calculate_fighter_position(int16_t accel_x);

#endif /* INC_AIRRACE_H_ */
