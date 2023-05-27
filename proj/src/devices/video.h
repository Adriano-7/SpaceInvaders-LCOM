#ifndef _LCOM_VIDEO_H_
#define _LCOM_VIDEO_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

int (video_set_mode)(uint16_t mode);

int (video_exit_mode)();

int (map_phys_mem) (uint16_t mode);

int (video_get_index)(uint16_t x, uint16_t y);

int (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (video_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (video_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (video_draw_xpm)(xpm_image_t xpm,uint8_t* img_colors, uint16_t x, uint16_t y);

int (erase_screen)();

#endif

