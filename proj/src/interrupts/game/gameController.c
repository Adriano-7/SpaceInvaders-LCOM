#include "gameController.h"

void (game_handle_keyboard)(enum Keys key, Player_t* player){
    if(key == Make_Arrow_left){
        movePlayer(player, LEFT);
    }
    else if(key == Make_Arrow_right){
        movePlayer(player, RIGHT);
    } 
}

void (game_handle_timer)(Entities_t* entities){
    moveMonster(entities->monsters);

    /*
    for(int i = 0; i < 2; i++){
        if(entities->gameObjects[i] != NULL){
            moveMonster(context->monsters[i]);
        }
    }
    */
    
    for(int i = 0; i < 2; i++){
        if(entities->gameObjects[i] != NULL){
            drawGameObject(entities->gameObjects[i]);
        }
    }
}
