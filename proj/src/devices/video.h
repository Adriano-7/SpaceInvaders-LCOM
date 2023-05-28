/**
 * @file video.h
 * @brief Functions for video mode and graphics operations.
 */

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

/**
 * @brief Sets the video mode.
 *
 * This function sets the video mode to the specified mode.
 *
 * @param mode The video mode to set.
 * @return Return 0 upon success, non-zero otherwise.
 */
int video_set_mode(uint16_t mode);

/**
 * @brief Exits the video mode.
 *
 * This function exits the current video mode and restores the previous mode.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int video_exit_mode();

/**
 * @brief Maps physical memory to virtual memory.
 *
 * This function maps the physical memory corresponding to the specified video mode to virtual memory.
 *
 * @param mode The video mode to map.
 * @return Return 0 upon success, non-zero otherwise.
 */
int map_phys_mem(uint16_t mode);

/**
 * @brief Gets the index of a pixel.
 *
 * This function calculates the index of a pixel at the specified coordinates.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return The index of the pixel.
 */
int video_get_index(uint16_t x, uint16_t y);

/**
 * @brief Draws a pixel on the screen.
 *
 * This function draws a pixel of the specified color at the specified coordinates.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 * @return Return 0 upon success, non-zero otherwise.
 */
int video_draw_pixel(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a horizontal line on the screen.
 *
 * This function draws a horizontal line of the specified length, starting from the specified coordinates,
 * with the specified color.
 *
 * @param x The x-coordinate of the starting point.
 * @param y The y-coordinate of the starting point.
 * @param len The length of the line.
 * @param color The color of the line.
 * @return Return 0 upon success, non-zero otherwise.
 */
int video_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a rectangle on the screen.
 *
 * This function draws a rectangle with the specified width and height, starting from the specified coordinates,
 * with the specified color.
 *
 * @param x The x-coordinate of the top-left corner of the rectangle.
 * @param y The y-coordinate of the top-left corner of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color of the rectangle.
 * @return Return 0 upon success, non-zero otherwise.
 */
int video_draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief Draws an XPM image on the screen.
 *
 * This function draws an XPM image at the specified coordinates, using the provided color map.
 *
 * @param xpm The XPM image to draw.
 * @param img_colors The color map of the XPM image.
 * @param x The x-coordinate of the top-left corner of the image.
 * @param y The y-coordinate of the top-left corner of the image.
 * @return Return 0 upon success, non-zero otherwise.
 */
int video_draw_xpm(xpm_image_t xpm, uint8_t* img_colors, uint16_t x, uint16_t y);

/**
 * @brief Erases the screen.
 *
 * This function fills the entire screen with black color, effectively erasing the contents.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int erase_screen();
