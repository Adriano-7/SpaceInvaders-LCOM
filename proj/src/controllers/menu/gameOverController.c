#include "gameOverController.h"

extern struct packet pkt;
extern GameOver_t* gameover;

void (game_over_handle_keyboard)(enum Keys key){
    if(key==Make_Esc){
        changeState(MENU);
    }
}

void (game_over_handle_timer)(){
    drawGameOver(gameover);
}

void game_over_handle_mouse(){
    updateCursor(gameover->cursor);
    game_over_option(gameover);
}


void game_over_option(){
    Cursor_t* cursor = gameover->cursor;
    if(cursor->lbPressed){
        for(int i=0; i<GAMEOVER_OPTIONS; i++){
            Option_t* option = gameover->options[i];
            if(cursor->drawableObject->x >= option->drawableObject->x && cursor->drawableObject->x <= option->drawableObject->x + option->drawableObject->img.width){
                if(cursor->drawableObject->y >= option->drawableObject->y && cursor->drawableObject->y <= option->drawableObject->y + option->drawableObject->img.height){
                    changeState(option->state);
                    gameover->firstTime = true;
                }
            }
        }
    }
}
