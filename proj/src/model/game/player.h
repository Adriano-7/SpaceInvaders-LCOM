#pragma once

#include <lcom/lcf.h>
#include "model/direction.h"
#include "../drawableObject.h"
#include "../../xpm/loadXpm.h"

/**
 * @struct Player
 * @brief Characterizes the player.
 * 
 */
typedef struct Player {
  DrawableObject_t* drawableObject;
  int lives;
  int score;
  int speedX;
} Player_t;

/**
 * @brief Create a Player object
 * 
 * @param speedX 
 * @return Player_t* 
 */
Player_t* createPlayer(int speedX);

/**
 * @brief Destroys the player.
 * 
 * @param player 
 */
void destroyPlayer(Player_t* player);

