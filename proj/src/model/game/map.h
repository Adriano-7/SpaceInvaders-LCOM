#pragma once
#include <lcom/lcf.h>
#include "player.h"
#include "monster.h"
#include "../drawableObject.h"

typedef struct Map{
    Player_t* player;
    Monster_t* monsters[55];
    drawableObject_t* drawableObjects[56];
} Map_t;


Map_t* createMap(Player_t* player, Monster_t* monsters[55], drawableObject_t* drawableObjects[56]);

Map_t* loadGame();
void destroyMap(Map_t* map);
