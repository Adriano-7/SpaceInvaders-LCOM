#pragma once
#include <lcom/lcf.h>
#include "player.h"
#include "monster.h"
#include "bullet.h"
#include "../drawableObject.h"

#include "constants.h"

typedef struct Map{
    Player_t* player;
    Monster_t* monsters[NUM_MONSTERS];
    Bullet_t* bullet;
    DrawableObject_t* drawableObjects[NUM_DRAWABLE_OBJECTS];

    int visibleMonsters;
} Map_t;


Map_t* createMap(Player_t* player, Monster_t* monsters[NUM_MONSTERS], Bullet_t* bullet, DrawableObject_t* drawableObjects[NUM_DRAWABLE_OBJECTS]);
Map_t* loadGame();

void drawMap(Map_t* map);
void drawScore(int score);
void drawLiveBar(int lives);
void resetMap(Map_t* map, bool decreaseLives, bool resetScore, bool resetLives);

void destroyMap(Map_t* map);