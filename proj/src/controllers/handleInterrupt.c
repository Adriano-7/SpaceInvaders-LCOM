#include "handleInterrupt.h"

int handle_keyboard(enum State* state, uint8_t bytes[2], Map_t* map, Menu_t* menu){
    enum Keys key = get_key(bytes);    

    switch(*state){
        case MENU:
            menu_handle_keyboard(key);
            break;
        case LEADERBOARD:
            break;
        case EXIT:
            break;
        case GAME:
            game_handle_keyboard(key, map);
            break;
        case PAUSE:
            break;
        case GAMEOVER:
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
            break;
        case EXIT:
            break;
        case GAME:
            game_handle_timer(map);
            break;
        case PAUSE:
            break;
        case GAMEOVER:
            break;
    }
    return 0;
}

int handle_mouse(enum State* state, Map_t* map, Menu_t* menu){
    switch(*state){
        case MENU:
            menu_handle_mouse(menu);
            break;
        case LEADERBOARD:
            break;
        case EXIT:
            break;
        case GAME:
            break;
        case PAUSE:
            break;
        case GAMEOVER:
            break;
    }
    
    return 0;
}
