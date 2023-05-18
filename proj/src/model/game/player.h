#pragma once

#include <lcom/lcf.h>
#include "model/direction.h"
#include "../gameObject.h"

typedef struct {
  GameObject* gameObject;
  bool canShoot;
  int lives;
  int score;
} Player;

Player* createPlayer();
void destroyPlayer(Player* player);

void movePlayer(Player* player, enum Direction direction);


