#pragma once
#include <lcom/lcf.h>
#include "player.h"
#include "monster.h"
#include "../drawableObject.h"

extern int timer_counter;

typedef struct Map{
    Player_t* player;
    Monster_t* monsters[55];
    drawableObject_t* drawableObjects[56];
} Map_t;


Map_t* createMap(Player_t* player, Monster_t* monsters[55], drawableObject_t* drawableObjects[56]);
Map_t* loadGame();

void drawMap(Map_t* map);
void drawScore(int score);
void drawLiveBar(int lives);

void destroyMap(Map_t* map);
