#include "gameController.h"

extern xpm_image_t letters_xpm[26];
extern xpm_image_t numbers_xpm[10];
extern xpm_image_t game_xpm[8];
extern vbe_mode_info_t mode_info;

extern int timer_counter;

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
    if(timer_counter % 30 == 0){
        for(int i = 0; i < 56; i++){
            if(entities->gameObjects[i] != NULL){
                entities->gameObjects[i]->cur_image = (entities->gameObjects[i]->cur_image + 1) % 2;
             }
        }
    }

    drawString("score:", mode_info.XResolution / 40, mode_info.YResolution / 40);
    drawScore(entities->player);
    drawLiveBar(entities->player);

    
}
