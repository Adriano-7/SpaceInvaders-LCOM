#include "menuController.h"

void (menu_handle_keyboard)(enum Keys key, Menu_t* menu, enum State* state){
    changeState(GAME);
}

void (menu_handle_timer)(Menu_t* menu){
    drawMenu(menu);
}

