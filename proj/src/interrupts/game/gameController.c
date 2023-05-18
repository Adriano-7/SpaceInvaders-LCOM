#include "gameController.h"

extern Player_t* player;
extern Monster_t* monster;

void (game_handle_keyboard)(enum Keys key){
    if(key == Make_Arrow_left){
        movePlayer(player, LEFT);
    }
    else if(key == Make_Arrow_right){
        movePlayer(player, RIGHT);
    } 
}

void (game_handle_timer)(){
    moveMonster(monster);
    /*
    for(int i = 0; i < 55; i++){
        if(monsters[i] != NULL){
            moveMonster(context->monsters[i]);
        }
    }
    */

    drawGameObject(monster->gameObject);
    drawGameObject(player->gameObject);

    /*
    for(int i = 0; i < 56; i++){
        if(gameObjects[i] != NULL){
            drawGameObject(context->gameObjects[i]);
        }
    }
    */
}
