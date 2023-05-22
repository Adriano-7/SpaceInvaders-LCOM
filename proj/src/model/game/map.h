#pragma once
#include <lcom/lcf.h>
#include "player.h"
#include "monster.h"
#include "gameObject.h"

typedef struct Map{
    Player_t* player;
    Monster_t* monsters[55];
    GameObject_t* gameObjects[56];
} Map_t;

Map_t* createMap(Player_t* player, Monster_t* monsters[55], GameObject_t* gameObjects[56]);
void destroyMap(Map_t* map);

Map_t* loadGame();
void freeGame();
