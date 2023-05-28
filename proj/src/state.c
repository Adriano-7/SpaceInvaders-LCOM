#include "state.h"

extern vbe_mode_info_t mode_info;

void changeState(enum State newState){
    erase_screen();
    *state = newState;
    erase_screen();
}
