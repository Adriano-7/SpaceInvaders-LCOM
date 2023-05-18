#pragma once

#include <lcom/lcf.h>
#include "model/game/player.h"
#include "model/game/monster.h"
#include "model/gameObject.h"

typedef struct Entities{
    Player_t* player;
    Monster_t* monsters;
    GameObject_t* gameObjects[2];
} Entities_t;

Entities_t* createEntities(Player_t* player, Monster_t* monsters, GameObject_t* gameObjects[2]);
void destroyEntities(Entities_t* entities);
