#ifndef _LCOM_VIDEO_H_
#define _LCOM_VIDEO_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

int (video_set_mode)(uint16_t mode);

int (video_exit_mode)();

int (map_phys_mem) (uint16_t mode);

uint32_t (correctColor) (uint32_t color);

int (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (video_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (video_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int video_draw_pattern(uint8_t no_rectangles, uint32_t first, uint8_t step);

uint32_t (color_indexed)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles);

uint32_t (color_direct)(uint16_t row, uint16_t col, uint8_t step, uint32_t first);

int (video_draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);

uint32_t (get_color)(uint16_t row, uint16_t col, uint8_t step, uint32_t first, uint8_t no_rectangles);

int (erase_screen)(uint16_t x, uint16_t y, xpm_image_t img);

bool pos_speed_update(bool verticalMovement, bool positiveMovement, uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed);

bool neg_speed_update(bool verticalMovement, bool positiveMovement, uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed, int* frameCounter);

bool coordinates_update(uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed, int* frameCounter, bool verticalMovement, bool positiveMovement);

#endif

