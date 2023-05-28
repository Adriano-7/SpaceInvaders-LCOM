#include "handleInterrupt.h"

extern uint8_t kbd_bytes[2];

int handle_keyboard(enum State* state){
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
            game_handle_keyboard(key);
            break;
        case GAMEOVER:
            game_over_handle_keyboard(key);
            break;
    }
    return 0;
}

int handle_timer(enum State* state){
    switch(*state){
        case MENU:
            menu_handle_timer();
            break;
        case LEADERBOARD:
            leaderboard_handle_timer();
            break;
        case EXIT:
            break;
        case GAME:
            game_handle_timer();
            break;
        case GAMEOVER:
            game_over_handle_timer();
            break;
    }
    return 0;
}


int handle_mouse(enum State* state){
    switch(*state){
        case MENU:
            menu_handle_mouse();
            break;
        case LEADERBOARD:
            break;
        case EXIT:
            break;
        case GAME:
            break;
        case GAMEOVER:
            game_over_handle_mouse();
            break;
    }
    
    return 0;
}
