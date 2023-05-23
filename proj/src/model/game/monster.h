#pragma once

#include <lcom/lcf.h>
#include "../drawableObject.h"
#include "../direction.h"

enum MonsterType {
  OSVALDO,
  IVAN,
  MIRO
};

typedef struct Monster {
  DrawableObject_t* drawableObject;
  enum MonsterType monsterType;
  int points;
  enum DirectionX direction;
  int speedX;
  int speedY;
  int cur_image;
} Monster_t;

Monster_t* createMonster(enum MonsterType monsterType, int x, int y, int speedX, int speedY);
void destroyMonster(Monster_t* monster);
void animateMonsters(Monster_t* monsters[55]);
void getMonsterImage(Monster_t* monster, int cur_image, xpm_image_t* img, uint8_t** img_colors);
int getMonsterImageIndex(enum MonsterType monsterType);
void changeMonsterDirection(Monster_t* monster);
