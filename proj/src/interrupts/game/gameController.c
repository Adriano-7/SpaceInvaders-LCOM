#include "gameController.h"

extern xpm_image_t letters_xpm[26];
extern xpm_image_t numbers_xpm[10];
extern xpm_image_t game_xpm[5];
extern vbe_mode_info_t mode_info;

void (game_handle_keyboard)(enum Keys key, Player_t* player){
    if(key == Make_Arrow_left){
        movePlayer(player, LEFT);
    }
    else if(key == Make_Arrow_right){
        movePlayer(player, RIGHT);
    } 
}

void (game_handle_timer)(Entities_t* entities){
    moveMonsters(entities->monsters);
    
    for(int i = 0; i < 56; i++){
        if(entities->gameObjects[i] != NULL){
            drawGameObject(entities->gameObjects[i]);
        }
    }
    drawString("score: ", mode_info.XResolution / 40, mode_info.YResolution / 40);
    
}
