#include <lcom/lcf.h>
#include "model/game/bullet.h"
#include "model/game/map.h"
#include "model/direction.h"
#include "../../../model/menu/leaderboard.h"

#include "../../../state.h"

extern vbe_mode_info_t mode_info;

void moveBullets(Map_t* map);

void playerBulletCollision(Map_t* map, Bullet_t* bullet);

void monsterBulletCollision(Map_t* map, Bullet_t* bullet);

bool detectObjectCollision(DrawableObject_t* obj1, DrawableObject_t* obj2);

void wallCollision(Bullet_t* bullet);
