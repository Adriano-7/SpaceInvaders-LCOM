#pragma once

#include <lcom/lcf.h>
#include "model/direction.h"
#include "../gameObject.h"

typedef struct Player {
  GameObject_t* gameObject;
  bool canShoot;
  int lives;
  int score;
} Player_t;

Player_t* createPlayer();
void destroyPlayer(Player_t* player);

void movePlayer(Player_t* player, enum Direction direction);


