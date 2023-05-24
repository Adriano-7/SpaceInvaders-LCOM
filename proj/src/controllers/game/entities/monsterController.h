#include <lcom/lcf.h>

#include "model/game/monster.h"
#include "model/game/map.h"
#include "model/direction.h"
#include "../../../state.h"


extern vbe_mode_info_t mode_info;


void moveMonsters(Map_t* map);

void moveMonstersY(Monster_t* monsters[NUM_MONSTERS]);

void moveMonstersX(Monster_t* monsters[NUM_MONSTERS]);

bool monstersCollidePlayer(Monster_t* monsters[NUM_MONSTERS], Player_t* player);

bool monstersCollideWalls(Monster_t* monsters[NUM_MONSTERS]);

bool detectCollision(DrawableObject_t* obj1, DrawableObject_t* obj2);
