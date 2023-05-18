#pragma once

#include <lcom/lcf.h>
#include "model/direction.h"
#include "../gameObject.h"

typedef struct {
  bool canShoot;
  int lives;
  int score;

  GameObject* gameObject;
} Player;

Player* createPlayer(GameObject* gameObject);
void movePlayer(Player* player, enum Direction direction);

