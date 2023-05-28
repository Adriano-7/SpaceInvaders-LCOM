#ifndef _LCOM_VIDEO_H_
#define _LCOM_VIDEO_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

/**
 * @brief Sets the mode.
 * 
 */
int (video_set_mode)(uint16_t mode);

/**
 * @brief Exists the mode.
 * 
 */
int (video_exit_mode)();

int (map_phys_mem) (uint16_t mode);

/**
 * @brief Gets the index.
 * 
 */
int (video_get_index)(uint16_t x, uint16_t y);

/**
 * @brief Draws the pixel.
 * 
 */
int (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws the hline.
 * 
 */
int (video_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws the rectangle.
 * 
 */
int (video_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief Draws the xpm.
 * 
 */
int (video_draw_xpm)(xpm_image_t xpm,uint8_t* img_colors, uint16_t x, uint16_t y);

/**
 * @brief Erases the screen.
 * 
 */
int (erase_screen)();

#endif

