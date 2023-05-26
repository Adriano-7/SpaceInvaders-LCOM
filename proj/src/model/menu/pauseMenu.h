#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include <stdlib.h>
#include "../drawableObject.h"
#include "option.h"
#include "../cursor.h"
#include "../../state.h"
#include "../constants.h"

extern vbe_mode_info_t mode_info;

typedef struct PauseMenu {
    Option_t* options[NUM_OPTIONS];
    Cursor_t* cursor;
    DrawableObject_t* drawableObjects[NUM_OPTIONS+2];
} PauseMenu_t;

PauseMenu_t* createPauseMenu(Option_t* options[NUM_OPTIONS], DrawableObject_t* drawableObjects[NUM_OPTIONS+2], Cursor_t* cursor);

#endif
