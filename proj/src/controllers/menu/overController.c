#include "overController.h"

void (over_handle_keyboard)(enum Keys key){
    if(key==Make_Esc){
        changeState(EXIT);
    }
}

void (over_handle_timer)(Over_t* over){
    drawOver(over);
}

void over_handle_mouse(Over_t* over){
    updateCursor(over->cursor, pp);
    sOption(over, pp);
}


void sOption(Over_t* over, struct packet pp){
    Cursor_t* cursor = over->cursor;
    if(cursor->lbPressed){
        for(int i=0; i<NUM_OPTIONS; i++){
            Option_t* option = over->options[i];
            if(cursor->drawableObject->x >= option->drawableObject->x && cursor->drawableObject->x <= option->drawableObject->x + option->drawableObject->img.width){
                if(cursor->drawableObject->y >= option->drawableObject->y && cursor->drawableObject->y <= option->drawableObject->y + option->drawableObject->img.height){
                    changeState(option->state);
                }
            }
        }
    }
}
