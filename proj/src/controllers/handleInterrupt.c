#include "handleInterrupt.h"
#include "model/game/player.h"

int handle_keyboard(enum State state, uint8_t bytes[2], Player* player){
    //enum Keys key = get_key(bytes);    

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
        //TODO
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
