#include "gameController.h"

extern xpm_image_t letters_xpm[26];
extern xpm_image_t numbers_xpm[10];
extern xpm_image_t game_xpm[8];
extern vbe_mode_info_t mode_info;

void (game_handle_keyboard)(enum Keys key, Map_t* map){
    if(key == Make_Arrow_left){
        movePlayer(map->player, LEFT);
    }
    else if(key == Make_Arrow_right){
        movePlayer(map->player, RIGHT);
    } 
    else if(key == Make_Spacebar){
        if(!map->player->isShooting){
            fireBullet(map->bullet, map->player->drawableObject->x, map->player->drawableObject->y + map->player->drawableObject->img->height, UP);
            map->player->isShooting = true;
        }
    }
}

void (game_handle_timer)(Map_t* map){
    moveMonsters(map->monsters);
    drawMap(map);
}  
