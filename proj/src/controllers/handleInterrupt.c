#include "handleInterrupt.h"

extern uint8_t kbd_bytes[2];

int handle_keyboard(enum State* state, Map_t* map, Menu_t* menu){
    enum Keys key = get_key(kbd_bytes);    

    switch(*state){
        case MENU:
            menu_handle_keyboard(key);
            break;
        case LEADERBOARD:
            leaderboard_handle_keyboard(key);
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
            leaderboard_handle_timer();
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
