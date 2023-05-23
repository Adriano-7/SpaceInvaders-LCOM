#pragma once
#include <lcom/lcf.h>
#include "player.h"
#include "monster.h"
#include "bullet.h"
#include "../drawableObject.h"

extern int timer_counter;

typedef struct Map{
    Player_t* player;
    Bullet_t* bullet;
    Monster_t* monsters[55];
    drawableObject_t* drawableObjects[57];
} Map_t;


Map_t* createMap(Player_t* player, Monster_t* monsters[55], Bullet_t* bullet, drawableObject_t* drawableObjects[57]);

void drawMap(Map_t* map);
void drawLiveBar(Player_t* player);
void drawScore(Player_t* player);

Map_t* loadGame();
void destroyMap(Map_t* map);
