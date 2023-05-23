#include "entitiesController.h"

extern vbe_mode_info_t mode_info;

void movePlayer(Player_t* player, enum DirectionX direction) {
  if(player == NULL) {
    printf("Error: player is NULL in movePlayer\n");
    exit(EXIT_FAILURE);
  }
  
  player->drawableObject->old_x = player->drawableObject->x;
  player->drawableObject->old_y = player->drawableObject->y;
    
  switch (direction) {
    case LEFT:
      if (player->drawableObject->x - player->speedX >= 0) {
        player->drawableObject->x -= player->speedX;
      }
      break;
    case RIGHT:
      if (player->drawableObject->x + player->speedX + player->drawableObject->img.width < mode_info.XResolution) {
        player->drawableObject->x += player->speedX;
      }
      break;
    default:
      break;
  }
}

void moveMonsters(Map_t* map){
    bool collideWithWalls = monstersCollideWalls(map->monsters);
    bool collideWithPlayer = monstersCollidePlayer(map->monsters, map->player);

    if(collideWithPlayer){
        map->player->lives--;
        if(map->player->lives == 0){
            map->player->drawableObject->isVisible = false;
        }
    }
    
    if(collideWithWalls){
        moveMonstersY(map->monsters);
        moveMonstersX(map->monsters);
    }
    else{
        moveMonstersX(map->monsters);
    }
}          

void moveMonstersY(Monster_t* monsters[55]){
    for (int i = 0; i < 55; i++) {
        bool canMoveDown = monsters[i]->drawableObject->y + monsters[i]->speedY + monsters[i]->drawableObject->img.height < mode_info.YResolution;

        if (monsters[i]->drawableObject->isVisible && canMoveDown) {
            changeMonsterDirection(monsters[i]);
            monsters[i]->drawableObject->old_y = monsters[i]->drawableObject->y;
            monsters[i]->drawableObject->y += monsters[i]->speedY;
        }
    }
}

void moveMonstersX(Monster_t* monsters[55]){
    for (int i = 0; i < 55; i++) {
        if (monsters[i]->drawableObject->isVisible) {
           enum DirectionX direction = monsters[i]->direction;
            monsters[i]->drawableObject->old_x = monsters[i]->drawableObject->x;
           if(direction == RIGHT){
                monsters[i]->drawableObject->x += monsters[i]->speedX;
           }
           else if(direction == LEFT){
                monsters[i]->drawableObject->x -= monsters[i]->speedX;
           }
        }
    }
}

bool monstersCollideWalls(Monster_t* monsters[55]){
  for(int i = 0; i < 55; i++){
    if(monsters[i]->drawableObject->isVisible){
      if((monsters[i]->direction==RIGHT) && (monsters[i]->drawableObject->x + monsters[i]->speedX + monsters[i]->drawableObject->img.width >= mode_info.XResolution)){
        return true;
      }
      else if((monsters[i]->direction==LEFT) && (monsters[i]->drawableObject->x - monsters[i]->speedX <= 0)){
        return true;
      }
    }
  }
  return false;
}

bool monstersCollidePlayer(Monster_t* monsters[55], Player_t* player){
  for(int i = 0; i < 55; i++){
    if(monsters[i]->drawableObject->isVisible){
      if(detectCollision(monsters[i]->drawableObject, player->drawableObject)){
        return true;
      }
    }
  }
  return false;
}

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

  for(int i = 0; i < 55; i++){
    if(map->monsters[i]->drawableObject->isVisible){
      if(detectCollision(bullet->drawableObject, map->monsters[i]->drawableObject)){
        
        vg_draw_rectangle(bullet->drawableObject->old_x, bullet->drawableObject->old_y, bullet->drawableObject->img.width, bullet->drawableObject->img.height, 0);
        bullet->drawableObject->isVisible = false;

        vg_draw_rectangle(map->monsters[i]->drawableObject->x, map->monsters[i]->drawableObject->y, map->monsters[i]->drawableObject->img.width+5, map->monsters[i]->drawableObject->img.height, 0);
        map->monsters[i]->drawableObject->isVisible = false;

        map->player->score += map->monsters[i]->points;
        map->player->isShooting = false;

        return;
      }
    }
  }

  if(bullet->drawableObject->y-bullet->drawableObject->img.height <= 0 || bullet->drawableObject->y >= mode_info.YResolution){
    vg_draw_rectangle(bullet->drawableObject->x, bullet->drawableObject->y, bullet->drawableObject->img.width, bullet->drawableObject->img.height+5, 0);
  
    bullet->drawableObject->isVisible = false;
    map->player->isShooting = false;
  }
}


bool detectCollision(DrawableObject_t* obj1, DrawableObject_t* obj2){
  if(obj1->x + obj1->img.width < obj2->x || obj1->x > obj2->x + obj2->img.width){
    return false;
  }
  if(obj1->y + obj1->img.height < obj2->y || obj1->y > obj2->y + obj2->img.height){
    return false;
  }
  return true;
}
