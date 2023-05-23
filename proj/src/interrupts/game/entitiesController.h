#include <lcom/lcf.h>
#include "model/game/player.h"
#include "model/game/monster.h"
#include "model/game/bullet.h"
#include "model/game/map.h"
#include "model/direction.h"


void movePlayer(Player_t* player, enum DirectionX direction);

void moveMonsters(Map_t* map);

void moveMonstersY(Monster_t* monsters[55]);

void moveMonstersX(Monster_t* monsters[55]);

bool monstersCollidePlayer(Monster_t* monsters[55], Player_t* player);

bool monstersCollideWalls(Monster_t* monsters[55]);

void moveBullet(Map_t* map);

bool detectCollision(DrawableObject_t* obj1, DrawableObject_t* obj2);
