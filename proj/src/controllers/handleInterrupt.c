#include "handleInterrupt.h"

extern Player_t* player;

int handle_keyboard(enum State state, uint8_t bytes[2], Player_t* player){
    enum Keys key = get_key(bytes);    

    switch(state){
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
            if(key == Make_Arrow_left){
                movePlayer(player, LEFT);
            }
            else if(key == Make_Arrow_right){
                movePlayer(player, RIGHT);
            } 
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
