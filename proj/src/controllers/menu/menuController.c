#include "menuController.h"

void (menu_handle_timer)(Menu_t* menu){
    drawMenu(menu);
}

void menu_handle_mouse(Menu_t* menu){
    updateCursor(menu->cursor, pp);
    selectOption(menu, pp);
}


void selectOption(Menu_t* menu, struct packet pp){
    Cursor_t* cursor = menu->cursor;
    if(cursor->lbPressed){
        for(int i=0; i<NUM_OPTIONS; i++){
            Option_t* option = menu->options[i];
            if(cursor->drawableObject->x >= option->drawableObject->x && cursor->drawableObject->x <= option->drawableObject->x + option->drawableObject->img.width){
                if(cursor->drawableObject->y >= option->drawableObject->y && cursor->drawableObject->y <= option->drawableObject->y + option->drawableObject->img.height){
                    changeState(option->state);
                }
            }
        }
    }
}
