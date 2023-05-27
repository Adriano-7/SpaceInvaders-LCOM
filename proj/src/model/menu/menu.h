/**
 * @file menu.h
 * @brief Definition of the Menu struct and related functions.
 */

#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include "../drawableObject.h"
#include "option.h"
#include "../cursor.h"
#include "../../state.h"
#include "../constants.h"

/**
 * @struct Menu
 * @brief Structure representing a menu.
 */
typedef struct Menu {
    Option_t* options[NUM_OPTIONS];                   /**< Array of menu options. */
    Cursor_t* cursor;                                 /**< Pointer to the menu cursor. */
    DrawableObject_t* drawableObjects[NUM_OPTIONS+2]; /**< Array of drawable objects associated with the menu. */
} Menu_t;

/**
 * @brief Creates a new Menu object.
 * @param options Array of menu options.
 * @param drawableObjects Array of drawable objects associated with the menu.
 * @param cursor Pointer to the menu cursor.
 * @return Pointer to the created Menu object.
 */
Menu_t* createMenu(Option_t* options[NUM_OPTIONS], DrawableObject_t* drawableObjects[NUM_OPTIONS+2], Cursor_t* cursor);

/**
 * @brief Loads a Menu object.
 * @return Pointer to the loaded Menu object.
 */
Menu_t* loadMenu();

/**
 * @brief Draws the menu on the screen.
 * @param menu Pointer to the Menu object.
 */
void drawMenu(Menu_t* menu);

/**
 * @brief Destroys a Menu object and frees the associated memory.
 * @param menu Pointer to the Menu object to be destroyed.
 */
void destroyMenu(Menu_t* menu);

#endif
