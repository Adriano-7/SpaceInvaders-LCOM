#include "bulletController.h"

void moveBullet(Map_t* map){
  Bullet_t* bullet = map->bullet;

  bullet->drawableObject->old_x = bullet->drawableObject->x;
  bullet->drawableObject->old_y = bullet->drawableObject->y;

  if(bullet->direction == UP){
    bullet->drawableObject->y -= bullet->speedY;
  }
  if(bullet->direction == DOWN){
    bullet->drawableObject->y += bullet->speedY;
  }

  for(int i = 0; i < NUM_MONSTERS; i++){
    if(map->monsters[i]->drawableObject->isVisible){
      if(detectBulletCollision(bullet->drawableObject, map->monsters[i]->drawableObject)){
        
        vg_draw_rectangle(bullet->drawableObject->old_x, bullet->drawableObject->old_y, bullet->drawableObject->img.width, bullet->drawableObject->img.height, 0);
        bullet->drawableObject->isVisible = false;

        vg_draw_rectangle(map->monsters[i]->drawableObject->x, map->monsters[i]->drawableObject->y, map->monsters[i]->drawableObject->img.width+5, map->monsters[i]->drawableObject->img.height, 0);
        map->monsters[i]->drawableObject->isVisible = false;
        map->visibleMonsters--;

        map->player->score += map->monsters[i]->points;
        map->player->isShooting = false;

        return;
      }
    }
  }

  if(bullet->drawableObject->y-bullet->drawableObject->img.height <= 0 || bullet->drawableObject->y >= mode_info.YResolution){
    vg_draw_rectangle(bullet->drawableObject->old_x, bullet->drawableObject->old_y, bullet->drawableObject->img.width, bullet->drawableObject->img.height, 0);
  
    bullet->drawableObject->isVisible = false;
    map->player->isShooting = false;
  }
}

bool detectBulletCollision(DrawableObject_t* obj1, DrawableObject_t* obj2){
  if(obj1->x + obj1->img.width < obj2->x || obj1->x > obj2->x + obj2->img.width){
    return false;
  }
  if(obj1->y + obj1->img.height < obj2->y || obj1->y > obj2->y + obj2->img.height){
    return false;
  }
  return true;
}

