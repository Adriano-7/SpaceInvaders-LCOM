#include "bulletController.h"

void moveBullets(Map_t* map){
  for(int i=0; i<NUM_BULLETS; i++){ 
    Bullet_t* bullet = map->bullets[i];
    if(bullet->drawableObject->isVisible){
      wallCollision(bullet);

      bullet->drawableObject->old_x = bullet->drawableObject->x;
      bullet->drawableObject->old_y = bullet->drawableObject->y;

      if(bullet->direction == UP){
        bullet->drawableObject->y -= bullet->speedY;
      }
      if(bullet->direction == DOWN){
        bullet->drawableObject->y += bullet->speedY;
      }

      if(bullet->type==PLAYER){playerBulletCollision(map, bullet);}
      if(bullet->type==MONSTER){monsterBulletCollision(map, bullet);}
    }
    else if(bullet->type==MONSTER  && rand()%(150)==0){
      int randomMonster = rand()%NUM_MONSTERS;
      if(map->monsters[randomMonster]->drawableObject->isVisible){
        fireBullet(bullet, map->monsters[randomMonster]->drawableObject, DOWN);
      }
    }
  }
}

void playerBulletCollision(Map_t* map, Bullet_t* bullet){
  for(int i = 0; i < NUM_MONSTERS; i++){
    if(map->monsters[i]->drawableObject->isVisible){
      if(detectObjectCollision(bullet->drawableObject, map->monsters[i]->drawableObject)){
        video_draw_rectangle(bullet->drawableObject->old_x, bullet->drawableObject->old_y, bullet->drawableObject->img.width, bullet->drawableObject->img.height, 0);
        bullet->drawableObject->isVisible = false;

        video_draw_rectangle(map->monsters[i]->drawableObject->x, map->monsters[i]->drawableObject->y, map->monsters[i]->drawableObject->img.width+5, map->monsters[i]->drawableObject->img.height, 0);
        map->monsters[i]->drawableObject->isVisible = false;
        map->visibleMonsters--;

        map->player->score += map->monsters[i]->points;
        map->bullets[0]->drawableObject->isVisible = false;
        return;
      }
    }
  }
}

void monsterBulletCollision(Map_t* map, Bullet_t* bullet){
  if(detectObjectCollision(bullet->drawableObject, map->player->drawableObject)){
    video_draw_rectangle(bullet->drawableObject->old_x, bullet->drawableObject->old_y, bullet->drawableObject->img.width, bullet->drawableObject->img.height, 0);
    bullet->drawableObject->isVisible = false;

    video_draw_rectangle(map->player->drawableObject->x, map->player->drawableObject->y, map->player->drawableObject->img.width, map->player->drawableObject->img.height, 0);

    map->bullets[0]->drawableObject->isVisible = false;

    resetMap(map, true, false, false, false);
  }
}

bool detectObjectCollision(DrawableObject_t* obj1, DrawableObject_t* obj2){
  if(obj1->x + obj1->img.width < obj2->x || obj1->x > obj2->x + obj2->img.width){
    return false;
  }
  if(obj1->y + obj1->img.height < obj2->y || obj1->y > obj2->y + obj2->img.height){
    return false;
  }
  return true;
}

void wallCollision(Bullet_t* bullet){
  if(bullet->drawableObject->y - bullet->drawableObject->img.height <= 0 || bullet->drawableObject->y + bullet->drawableObject->img.height >= mode_info.YResolution-30){
    video_draw_rectangle(bullet->drawableObject->x, bullet->drawableObject->y, bullet->drawableObject->img.width, bullet->drawableObject->img.height, 0);
    bullet->drawableObject->isVisible = false;
  }
}

