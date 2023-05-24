#include "state.h"
#include "devices/graphics.h"

extern vbe_mode_info_t mode_info;

void changeState(enum State* state, enum State newState){
    vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0);
    *state = newState;
}
