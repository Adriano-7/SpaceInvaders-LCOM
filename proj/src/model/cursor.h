/**
 * @file cursor.h
 * @brief Definition of the Cursor struct and related functions.
 */

#pragma once

#include <lcom/lcf.h>
#include "drawableObject.h"
#include "../devices/mouse.h"
#include "../state.h"

/**
 * @struct Cursor
 * @brief Structure representing a cursor.
 */
typedef struct Cursor {
    DrawableObject_t* drawableObject; /**< The drawable object associated with the cursor. */
    bool lbPressed;                  /**< Flag indicating whether the left button is pressed. */
} Cursor_t;

/**
 * @brief Creates a new Cursor object.
 * @return Pointer to the created Cursor object.
 */
Cursor_t* createCursor();

/**
 * @brief Updates the Cursor position and button state based on the mouse input.
 * @param cursor Pointer to the Cursor object.
 * @param pp Mouse packet containing the mouse input data.
 */
void updateCursor(Cursor_t* cursor, struct packet pp);

/**
 * @brief Destroys a Cursor object and frees the associated memory.
 * @param cursor Pointer to the Cursor object to be destroyed.
 */
void destroyCursor(Cursor_t* cursor);

