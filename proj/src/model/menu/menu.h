#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <string.h>
#include "../drawableObject.h"

typedef struct Menu{
    //Option_t* options[2];
    DrawableObject_t* drawableObjects[4];
} Menu_t;

Menu_t* createMenu();
void drawMenu(Menu_t* menu);

#endif
