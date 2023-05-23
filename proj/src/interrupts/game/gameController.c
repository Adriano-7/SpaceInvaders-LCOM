#include "gameController.h"

void (game_handle_keyboard)(enum Keys key, Map_t* map){
    if(key == Make_Arrow_left){
        movePlayer(map->player, LEFT);
    }
    else if(key == Make_Arrow_right){
        movePlayer(map->player, RIGHT);
    } 
}

void (game_handle_timer)(Map_t* map){
    moveMonsters(map->monsters);
    drawMap(map);
}  
