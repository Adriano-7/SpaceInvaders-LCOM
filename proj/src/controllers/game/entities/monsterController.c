#include "monsterController.h"

void moveMonsters(Map_t* map){
    bool collideWithWalls = monstersCollideWalls(map->monsters);
    bool collideWithPlayer = monstersCollidePlayer(map->monsters, map->player);

    if(collideWithPlayer){
      resetMap(map, true, false, false, false);
    }
    
    if(collideWithWalls){
        moveMonstersY(map->monsters);
        moveMonstersX(map->monsters);
    }
    else{
        moveMonstersX(map->monsters);
    }
}          

void moveMonstersY(Monster_t* monsters[NUM_MONSTERS]){
    for (int i = 0; i < NUM_MONSTERS; i++) {
        bool canMoveDown = monsters[i]->drawableObject->y + monsters[i]->speedY + monsters[i]->drawableObject->img.height < mode_info.YResolution;

        if (monsters[i]->drawableObject->isVisible && canMoveDown) {
            changeMonsterDirection(monsters[i]);
            monsters[i]->drawableObject->old_y = monsters[i]->drawableObject->y;
            monsters[i]->drawableObject->y += monsters[i]->speedY;
        }
    }
}

void moveMonstersX(Monster_t* monsters[NUM_MONSTERS]){
    for (int i = 0; i < NUM_MONSTERS; i++) {
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

bool monstersCollideWalls(Monster_t* monsters[NUM_MONSTERS]){
  for(int i = 0; i < NUM_MONSTERS; i++){
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

bool monstersCollidePlayer(Monster_t* monsters[NUM_MONSTERS], Player_t* player){
  for(int i = 0; i < NUM_MONSTERS; i++){
    if(monsters[i]->drawableObject->isVisible){
      if(detectCollision(monsters[i]->drawableObject, player->drawableObject)){
        return true;
      }
    }
  }
  return false;
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
