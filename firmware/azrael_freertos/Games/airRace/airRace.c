///*
// * airRace.c
// *
// *  Created on: May 3, 2026
// *      Author: hillary
// */
//
#include "airRace.h"
#include <stdio.h>
#include <stdlib.h>

//static void display_start_screen(uint8_t *play_game);
//static void display_game_over_screen(uint8_t *play_game);
//
//static void steer_fighter(Fighter_Typedef *fighter);
//static void update_obstacles(Obstacle_Typedef *obs);
//static uint8_t check_if_hit_fighter(Obstacle_Typedef *obs, Fighter_Typedef *fighter);
//static void check_out_of_bounds(Obstacle_Typedef *obs);
//
//void init_game(Obstacle_Typedef *obs_arr, Fighter_Typedef *fighter) {
//
//	srand(49250);
//	for(uint8_t i = 0; i < OBSTACLES_NO; i++){
//		obs_arr[i].current_x = (((rand() % DISPLAY_WIDTH) / 32) * 32);
//		obs_arr[i].current_y = -(((rand() % 200) / (FIGHTER_HEIGHT + 10)) * (FIGHTER_HEIGHT + 10));
//		obs_arr[i].obstacle_img = (const uint16_t *) obstacle_image;
//	}
//
//
//
//}
//
////void start_game() {
////	uint8_t play_game = 0;
////
////	do {
////		uint8_t fps = 0;
////		Obstacle_Typedef obs_arr[OBSTACLES_NO];
////		Fighter_Typedef fighter_jet;
////		init_game((Obstacle_Typedef *)&obs_arr, &fighter_jet);
////
////		while (1) {
////			fps++;
////
////
////			if(REFRESH){
////				char str[10];
////				sprintf(str, "fps: %d", fps);
////				display_print_str_bg(0, 0, str, Font_7x10, ST7735_RED, ST7735_BLACK);
////				fps = 0;
////				REFRESH = 0;
////			}
////
////			LIS3DH_Data accel;
////			LIS3DH_Tilt tilt;
////			update_obstacles((Obstacle_Typedef *)&obs_arr);
////			lis3dh_readXYZ(&accel);
////			lis3dh_getTilt(&accel, &tilt);
////			steer_fighter(&fighter_jet);
////			check_out_of_bounds((Obstacle_Typedef *)&obs_arr);
////			if (check_if_hit_fighter((Obstacle_Typedef *)&obs_arr, &fighter_jet))
////				break;
////
////		}
////		display_game_over_screen(&play_game);
////	} while(play_game);
////
////}
//
//static void display_start_screen(uint8_t *play_game) {
//	ST7735_FillRectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, ST7735_BLACK);
//
//	char str[30] = "AIR";
//	display_print_str(38, 20, str, Font_16x26, ST7735_YELLOW);
//	sprintf(str, "RACE");
//	display_print_str(31, 48, str, Font_16x26, ST7735_YELLOW);
//	sprintf(str, "Press OK to start");
//	display_print_str(5, 100, str, Font_7x10, ST7735_RED);
//	sprintf(str, "Press EXIT to quit");
//	display_print_str(1, 114, str, Font_7x10, ST7735_RED);
//
////	osEventFlagsWait(SystemFlagsHandle, START_A, osFlagsWaitAny, osWaitForever);
//	*play_game = 1;
//	osDelay(10);
//
//}
//
//static void display_game_over_screen(uint8_t *play_game){
//	char msg[30] = "GAME OVER";
//	display_print_str(14, 60, msg, Font_11x18, ST7735_CYAN);
//	sprintf(msg, "Press OK to restart");
//	display_print_str(0, 100, msg, Font_7x10, ST7735_RED);
//	sprintf(msg, "Press EXIT to quit");
//	display_print_str(1, 114, msg, Font_7x10, ST7735_RED);
//
//	uint32_t flags = osEventFlagsWait(SystemFlagsHandle, PRESSED_OK | PRESSED_EXIT, osFlagsWaitAny, osWaitForever);
//
//	if(flags && PRESSED_OK){
//		*play_game = 1;
//
//	} else if(flags && PRESSED_EXIT){
//		*play_game = 0;
//
//	}
//}
//
uint8_t calculate_fighter_position(int16_t accel_x){
	uint8_t new_x = (DISPLAY_WIDTH * (accel_x + LIS3DH_TILT_THRESHOLD)) / (2 * LIS3DH_TILT_THRESHOLD);
	return (new_x / (DISPLAY_WIDTH / DISP_DIV)) * (DISPLAY_WIDTH / DISP_DIV);

}
//
//static void steer_fighter(Fighter_Typedef *fighter) {
//
//	int8_t current_x = fighter->current_x;
//
//	if (fighter->current_x != current_x) {
//
//		ST7735_FillRectangle(0, FIGHTER_Y, DISPLAY_WIDTH, FIGHTER_HEIGHT,
//		ST7735_BLACK);
//		ST7735_DrawImageTransparent(current_x, FIGHTER_Y, FIGHTER_WIDTH, FIGHTER_HEIGHT,
//				(const uint16_t*) fighter->fighter_img, ST7735_BLACK);
//	}
//
//	fighter->current_x = current_x;
//}
//
//static void update_obstacles(Obstacle_Typedef *obs_arr) {
//
//	for(uint8_t i = 0; i < OBSTACLES_NO; i++){
//		obs_arr[i].current_y += OBSTACLE_SPEED;
//		int16_t clear_rect_y = obs_arr[i].current_y - OBSTACLE_SPEED;
//		ST7735_FillRectangle(obs_arr[i].current_x, clear_rect_y, OBSTACLE_WIDTH, (OBSTACLE_HEIGHT - OBSTACLE_SPEED - 10), ST7735_BLACK);
//		ST7735_DrawImageTransparent(obs_arr[i].current_x, obs_arr[i].current_y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT, obs_arr[i].obstacle_img, ST7735_BLACK);
//	}
//}
//
//static uint8_t check_if_hit_fighter(Obstacle_Typedef *obs_arr, Fighter_Typedef *fighter) {
//	for(uint8_t i = 0; i < OBSTACLES_NO; i++){
//		uint8_t min = (fighter->current_x > obs_arr[i].current_x && fighter->current_x < (obs_arr[i].current_x + OBSTACLE_WIDTH)) ? 1 : 0;
//		uint8_t max = ((fighter->current_x + FIGHTER_WIDTH) > obs_arr[i].current_x && (fighter->current_x + FIGHTER_WIDTH) < (obs_arr[i].current_x + OBSTACLE_WIDTH)) ? 1 : 0;
//		if ((obs_arr[i].current_y + OBSTACLE_HEIGHT) > FIGHTER_Y && obs_arr[i].current_y < DISPLAY_HEIGHT) {
//			if (min||max) {
//				return 1;
//			}
//		}
//	}
//	return 0;
//}
//
//static void check_out_of_bounds(Obstacle_Typedef *obs_arr){
//	for(uint8_t i = 0; i < OBSTACLES_NO; i++){
//		if(obs_arr[i].current_y > (DISPLAY_HEIGHT + OBSTACLE_HEIGHT)){
//			obs_arr[i].current_x = (((rand() % DISPLAY_WIDTH) / 32) * 32);
//			obs_arr[i].current_y = -OBSTACLE_HEIGHT;
//		}
//	}
//}
//
