#include "handleInterrupt.h"

extern enum State* state;

int handle_keyboard(uint8_t bytes[2]){
    enum Keys key = get_key(bytes);    

    switch(*state){
        case MENU:
            //TODO
            break;
        case LEADERBOARD:
            //TODO
            break;
        case EXIT:
            //TODO
            break;
        case GAME:
            game_handle_keyboard(key);
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

int handle_timer(){
    switch(*state){
        case MENU:
            //TODO
            break;
        case LEADERBOARD:
            //TODO
            break;
        case EXIT:
            //TODO
            break;
        case GAME:
            game_handle_timer();
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
