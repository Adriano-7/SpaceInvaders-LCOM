#include "leaderboardController.h"

void leaderboard_handle_keyboard(enum Keys key){
    if(key == Make_Esc){
        changeState(MENU);
    }
}

void leaderboard_handle_timer(){
    drawLeaderboard();
}
