/**
 * @file drawableObject.h
 * @brief Definition and functions for the DrawableObject structure.
 */

#pragma once

#include <lcom/lcf.h>
#include "../devices/video.h"

/**
 * @struct DrawableObject
 * @brief Structure representing a drawable object with position, image, and visibility.
 */
typedef struct DrawableObject {
    int x;                /**< The x-coordinate of the object's position. */
    int y;                /**< The y-coordinate of the object's position. */
    int old_x;            /**< The previous x-coordinate of the object's position. */
    int old_y;            /**< The previous y-coordinate of the object's position. */
    xpm_image_t img;      /**< The image associated with the object. */
    uint8_t* img_colors;  /**< The color map associated with the image. */
    bool isVisible;       /**< Flag indicating whether the object is visible or hidden. */
} DrawableObject_t;

/**
 * @brief Creates a new DrawableObject.
 *
 * @param x The initial x-coordinate of the object's position.
 * @param y The initial y-coordinate of the object's position.
 * @param img The image associated with the object.
 * @param img_colors The color map associated with the image.
 * @param isVisible Flag indicating whether the object is visible or hidden.
 * @return A pointer to the newly created DrawableObject.
 */
DrawableObject_t* createdrawableObject(int x, int y, xpm_image_t img, uint8_t* img_colors, bool isVisible);

/**
 * @brief Draws a DrawableObject on the screen.
 *
 * @param obj The DrawableObject to be drawn.
 */
void drawdrawableObject(DrawableObject_t* obj);
