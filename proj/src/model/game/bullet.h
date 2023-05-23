#pragma once

#include <lcom/lcf.h>
#include "model/direction.h"
#include "../drawableObject.h"
#include "../../xpm/loadXpm.h"

typedef struct Bullet {
  drawableObject_t* drawableObject;
  enum DirectionY direction;
  int speedY;
} Bullet_t;

Bullet_t* createBullet(int x, int y, int speedX);
void destroyBullet(Bullet_t* bullet);
void fireBullet(Bullet_t* bullet, int x, int y, enum DirectionY direction);
