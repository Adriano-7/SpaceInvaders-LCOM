#pragma once

#include <stdlib.h>
#include "../drawableObject.h"
#include "option.h"
#include "../cursor.h"
#include "../../state.h"
#include "../constants.h"
#include "../game/map.h"


extern vbe_mode_info_t mode_info;
extern Map_t* map;

typedef struct GameOver{
    bool firstTime;
    Option_t* options[GAMEOVER_OPTIONS];
    Cursor_t* cursor;
    DrawableObject_t* drawableObjects[GAMEOVER_NUM_DRAWABLE_OBJECTS];
} GameOver_t;

GameOver_t* createGameOver(Option_t* options[GAMEOVER_OPTIONS], DrawableObject_t* drawableObjects[GAMEOVER_NUM_DRAWABLE_OBJECTS], Cursor_t* cursor);

GameOver_t* loadGameOver();

void drawGameOver(GameOver_t* over);

void destroyGameOver(GameOver_t* over);
