#include "gameController.h"

extern xpm_image_t letters_xpm[26];
extern xpm_image_t numbers_xpm[10];
extern xpm_image_t game_xpm[8];
extern vbe_mode_info_t mode_info;

extern int timer_counter;

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
    
    for(int i = 0; i < 56; i++){
        if(map->drawableObjects[i] != NULL){
            drawdrawableObject(map->drawableObjects[i]);
        }
    }
    if(timer_counter % 30 == 0){
        for(int i = 0; i < 56; i++){
            if(map->drawableObjects[i] != NULL){
                map->drawableObjects[i]->cur_image = (map->drawableObjects[i]->cur_image + 1) % 2;
             }
        }
    }

    drawString("score:", mode_info.XResolution / 40, mode_info.YResolution / 40);
    drawScore(map->player);
    drawLiveBar(map->player);
}  
