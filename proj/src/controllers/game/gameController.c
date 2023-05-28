#include "gameController.h"

void (game_handle_keyboard)(enum Keys key, Map_t* map){
    if(key == Make_Arrow_left){
        movePlayer(map->player, LEFT);
    }
    else if(key == Make_Arrow_right){
        movePlayer(map->player, RIGHT);
    } 
    else if(key == Make_Spacebar){
        fireBullet(map->bullets[0], map->player->drawableObject, UP);
    }
    else if(key==Make_Esc){
        addScore(map->player->score);
        resetMap(map, false, true, true, true);
        changeState(MENU);
    }
}

void (game_handle_timer)(Map_t* map){
    if(timer_counter % 30 == 0){
        animateMonsters(map->monsters);
    }

    moveMonsters(map);
    moveBullets(map);
    drawMap(map);
}  

