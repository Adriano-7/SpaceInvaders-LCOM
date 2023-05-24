#pragma once
#include <lcom/lcf.h>
#include "model/direction.h"
#include "../drawableObject.h"
#include "../../xpm/loadXpm.h"

typedef struct Bullet {
  DrawableObject_t* drawableObject;
  enum DirectionY direction;
  int speedY;
} Bullet_t;

Bullet_t* createBullet(int x, int y, int speedX, enum DirectionY direction);
void fireBullet(Bullet_t* bullet, DrawableObject_t* shooter, enum DirectionY direction);
void destroyBullet(Bullet_t* bullet);
