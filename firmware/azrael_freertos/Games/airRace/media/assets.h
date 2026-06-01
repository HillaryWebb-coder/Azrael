/*
 * assets.h
 *
 *  Created on: May 3, 2026
 *      Author: hillary
 */

#ifndef GAMES_AIRRACE_MEDIA_ASSETS_H_
#define GAMES_AIRRACE_MEDIA_ASSETS_H_

#include <stdint.h>

#define FIGHTER_HEIGHT 20
#define FIGHTER_WIDTH 20

#define OBSTACLE_WIDTH 25
#define OBSTACLE_HEIGHT 25

#define EXPLOSION_WIDTH 30
#define EXPLOSION_HEIGHT 30

extern const uint16_t fighter_image[FIGHTER_HEIGHT][FIGHTER_WIDTH];
extern const uint16_t obstacle_image[OBSTACLE_HEIGHT][OBSTACLE_WIDTH];
extern const uint16_t explosion_image[EXPLOSION_HEIGHT][EXPLOSION_WIDTH];

#endif /* GAMES_AIRRACE_MEDIA_ASSETS_H_ */
