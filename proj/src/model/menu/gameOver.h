#pragma once

#include <stdlib.h>
#include "../drawableObject.h"
#include "option.h"
#include "../cursor.h"
#include "../../state.h"
#include "../constants.h"
#include "../game/map.h"
#include "../../xpm/loadXpm.h"

extern vbe_mode_info_t mode_info;
extern Map_t* map;

/**
 * @struct GameOver
 * @brief Responsible for Game Over.
 * 
 */
typedef struct GameOver{
    bool firstTime;
    Option_t* options[GAMEOVER_OPTIONS];
    Cursor_t* cursor;
    DrawableObject_t* drawableObjects[GAMEOVER_NUM_DRAWABLE_OBJECTS];
} GameOver_t;

/**
 * @brief Create a Game Over object
 * 
 * @param options 
 * @param drawableObjects 
 * @param cursor 
 * @return GameOver_t* 
 */
GameOver_t* createGameOver(Option_t* options[GAMEOVER_OPTIONS], DrawableObject_t* drawableObjects[GAMEOVER_NUM_DRAWABLE_OBJECTS], Cursor_t* cursor);

/**
 * @brief Loads Game Over.
 * 
 * @return GameOver_t* 
 */
GameOver_t* loadGameOver();

/**
 * @brief Draws the game over.
 * 
 * @param over 
 */
void drawGameOver(GameOver_t* over);

/**
 * @brief Destroys Game Over.
 * 
 * @param over 
 */
void destroyGameOver(GameOver_t* over);
