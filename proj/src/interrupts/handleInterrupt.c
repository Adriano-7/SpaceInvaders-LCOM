#include "handleInterrupt.h"

int handle_keyboard(enum State* state, uint8_t bytes[2], Player_t* player){
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
            game_handle_keyboard(key, player);
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

int handle_timer(enum State* state, Entities_t *entities){
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
            game_handle_timer(entities);
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
