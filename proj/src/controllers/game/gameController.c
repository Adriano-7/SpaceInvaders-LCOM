#include "gameController.h"

void (game_handle_keyboard)(enum Keys key, Map_t* map){
    if(key == Make_Arrow_left){
        movePlayer(map->player, LEFT);
    }
    else if(key == Make_Arrow_right){
        movePlayer(map->player, RIGHT);
    } 
    else if(key == Make_Spacebar){
        if(!map->player->isShooting){
            map->player->isShooting = true;
            fireBullet(map->bullet, map->player->drawableObject, UP);
        }
    }
}

void (game_handle_timer)(Map_t* map){
    if(timer_counter % 30 == 0){
        animateMonsters(map->monsters);
    }

    moveMonsters(map);
    if(map->bullet->drawableObject->isVisible==true){
        moveBullet(map);
    }
    drawMap(map);
}  

