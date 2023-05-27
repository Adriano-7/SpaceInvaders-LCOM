#pragma once

#include <stdlib.h>
#include "../drawableObject.h"
#include "option.h"
#include "../cursor.h"
#include "../../state.h"
#include "../constants.h"


extern vbe_mode_info_t mode_info;

typedef struct Over{
    Option_t* options[NUM_OPTIONS];
    Cursor_t* cursor;
    DrawableObject_t* drawableObjects[NUM_OPTIONS+2];
} Over_t;

Over_t* createOver(Option_t* options[NUM_OPTIONS], DrawableObject_t* drawableObjects[NUM_OPTIONS+2], Cursor_t* cursor);

Over_t* loadOver();

void drawOver(Over_t* over);

void destroyOver(Over_t* over);
