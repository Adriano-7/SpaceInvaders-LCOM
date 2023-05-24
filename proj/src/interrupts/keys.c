#include "keys.h"

enum Keys get_key(uint8_t bytes[2]) {
    if (bytes[0] == 0xE0) {
        switch (bytes[1]) {
            case 0x4B:
                return Make_Arrow_left;
            case 0x4D:
                return Make_Arrow_right;
            default:
                return KEY_NONE;
        }
    } 
    else{
        switch (bytes[0]) {
            case 0x39:
                return Make_Spacebar;
            default:
                return KEY_NONE;
        }
    }
    return KEY_NONE;
}
