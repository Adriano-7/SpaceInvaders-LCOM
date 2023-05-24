#include "handleInterrupt.h"

int handle_keyboard(enum State* state, uint8_t bytes[2], Map_t* map, Menu_t* menu){
    enum Keys key = get_key(bytes);    

    switch(*state){
        case MENU:
            menu_handle_keyboard(key, menu, state);
            break;
        case LEADERBOARD:
            //TODO
            break;
        case EXIT:
            //TODO
            break;
        case GAME:
            game_handle_keyboard(key, map);
            break;
        case PAUSE:
            //TODO
            break;
        case GAMEOVER:
            //TODO
            break;
          
    }
    return 0;
}

int handle_timer(enum State* state, Map_t *map, Menu_t* menu){
    switch(*state){
        case MENU:
            menu_handle_timer(menu);
            break;
        case LEADERBOARD:
            //TODO
            break;
        case EXIT:
            //TODO
            break;
        case GAME:
            game_handle_timer(map);
            break;
        case PAUSE:
            //TODO
            break;
        case GAMEOVER:
            //TODO
            break;
    }
    return 0;
}
