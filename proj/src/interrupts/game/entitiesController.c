#include "entitiesController.h"

extern vbe_mode_info_t mode_info;

void movePlayer(Player_t* player, enum Direction direction) {
  if(player == NULL) {
    printf("Error: player is NULL in movePlayer\n");
    exit(EXIT_FAILURE);
  }
  
  player->gameObject->old_x = player->gameObject->x;
  player->gameObject->old_y = player->gameObject->y;
    
  switch (direction) {
    case LEFT:
      if (player->gameObject->x - player->speedX >= 0) {
        player->gameObject->x -= player->speedX;
      }
      break;
    case RIGHT:
      if (player->gameObject->x + player->speedX + player->gameObject->img[player->gameObject->cur_image].width < mode_info.XResolution) {
        player->gameObject->x += player->speedX;
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
        bool canMoveDown = monsters[i]->gameObject->y + monsters[i]->speedY + monsters[i]->gameObject->img[monsters[i]->gameObject->cur_image].height < mode_info.YResolution;

        if (monsters[i]->isAlive && canMoveDown) {
            changeMonsterDirection(monsters[i]);
            monsters[i]->gameObject->old_y = monsters[i]->gameObject->y;
            monsters[i]->gameObject->y += monsters[i]->speedY;
        }
    }
}

void moveMonstersX(Monster_t* monsters[55]){
    for (int i = 0; i < 55; i++) {
        if (monsters[i]->isAlive) {
           enum Direction direction = monsters[i]->direction;
            monsters[i]->gameObject->old_x = monsters[i]->gameObject->x;
           if(direction == RIGHT){
                monsters[i]->gameObject->x += monsters[i]->speedX;
           }
           else if(direction == LEFT){
                monsters[i]->gameObject->x -= monsters[i]->speedX;
           }
        }
    }
}

bool monstersCollide(Monster_t* monsters[55]){
  for(int i = 0; i < 55; i++){
    if(monsters[i]->isAlive){
      
      if((monsters[i]->direction==RIGHT) && (monsters[i]->gameObject->x + monsters[i]->speedX + monsters[i]->gameObject->img[monsters[i]->gameObject->cur_image].width >= mode_info.XResolution)){
        return true;
      }
      else if((monsters[i]->direction==LEFT) && (monsters[i]->gameObject->x - monsters[i]->speedX <= 0)){
        return true;
      }
    }
  }
  return false;
}
