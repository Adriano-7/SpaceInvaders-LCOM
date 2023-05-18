#pragma once

#include <lcom/lcf.h>
#include "../gameObject.h"
#include "../direction.h"

enum MonsterType {
  OSVALDO,
  IVAN,
  MIRO
};

typedef struct Monster {
  GameObject_t* gameObject;
  int points;
  bool isAlive;
  enum Direction direction;
} Monster_t;

Monster_t* createMonster(enum MonsterType monsterType, int x, int y);
void destroyMonster(Monster_t* monster);
int getMonsterImageIndex(enum MonsterType monsterType);

void moveMonster(Monster_t* monster);
