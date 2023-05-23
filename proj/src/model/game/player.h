#pragma once

#include <lcom/lcf.h>
#include "model/direction.h"
#include "../drawableObject.h"
#include "../../xpm/loadXpm.h"

typedef struct Player {
  DrawableObject_t* drawableObject;
  bool canShoot;
  int lives;
  int score;
  int speedX;
} Player_t;

Player_t* createPlayer(int speedX);
void destroyPlayer(Player_t* player);
