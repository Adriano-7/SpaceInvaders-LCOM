#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include "../drawableObject.h"
#include "option.h"
#include "../cursor.h"
#include "../../state.h"
#include "../constants.h"

extern vbe_mode_info_t mode_info;

typedef struct Menu{
    bool firstTime;
    Option_t* options[NUM_OPTIONS];
    Cursor_t* cursor;
    DrawableObject_t* drawableObjects[NUM_OPTIONS+2];
} Menu_t;

Menu_t* createMenu(Option_t* options[NUM_OPTIONS], DrawableObject_t* drawableObjects[NUM_OPTIONS+2], Cursor_t* cursor);

Menu_t* loadMenu();

void drawMenu(Menu_t* menu);

void destroyMenu(Menu_t* menu);

#endif
