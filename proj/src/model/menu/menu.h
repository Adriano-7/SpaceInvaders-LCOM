#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <string.h>
#include "../gameObject.h"

typedef struct Menu{
    //Option_t* options[2];
    GameObject_t* gameObjects[4];
} Menu_t;

Menu_t* createMenu();
void drawMenu(Menu_t* menu);

#endif
