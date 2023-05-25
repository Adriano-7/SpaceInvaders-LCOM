#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include "../drawableObject.h"
#include "option.h"
#include "../../state.h"
#include "../constants.h"

extern vbe_mode_info_t mode_info;

typedef struct Menu{
    Option_t* options[NUM_OPTIONS];
    DrawableObject_t* drawableObjects[NUM_OPTIONS+1];
} Menu_t;

Menu_t* createMenu(Option_t* options[NUM_OPTIONS], DrawableObject_t* drawableObjects[NUM_OPTIONS+1]);
Menu_t* loadMenu();
void drawMenu(Menu_t* menu);

void destroyMenu(Menu_t* menu);

#endif
