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

void moveMonsters(Monster_t* monsters[55]){
    bool collide = monstersCollide(monsters);
   
    
    if(collide){
        moveMonstersY(monsters);
        moveMonstersX(monsters);
    }
    else{
        moveMonstersX(monsters);
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

bool monstersCollide(Monster_t* monsters[55]){
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

}
