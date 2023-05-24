#include <lcom/lcf.h>
#include "model/game/bullet.h"
#include "model/game/map.h"
#include "model/direction.h"

extern vbe_mode_info_t mode_info;

void moveBullet(Map_t* map);

bool detectBulletCollision(DrawableObject_t* obj1, DrawableObject_t* obj2);
