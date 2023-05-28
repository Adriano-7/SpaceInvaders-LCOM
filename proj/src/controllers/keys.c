#include "keys.h"

enum Keys get_key(uint8_t bytes[2]) {
    if (bytes[0] == KEYBOARD_TWO_BYTE) {
        switch (bytes[1]) {
            case KEY_ARROW_LEFT_MAKE:
                return Make_Arrow_left;
            case KEY_ARROW_RIGHT_MAKE:
                return Make_Arrow_right;
            default:
                return KEY_NONE;
        }
    } 
    else{
        switch (bytes[0]) {
            case KEY_SPACEBAR_MAKE:
                return Make_Spacebar;
            case KEY_ESC_MAKE:
                return Make_Esc;
            default:
                return KEY_NONE;
        }
    }
    return KEY_NONE;
}
