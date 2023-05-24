#pragma once
#include <lcom/lcf.h>
#include <stdint.h>

enum Keys {
    Make_Arrow_left,
    Make_Arrow_right,
    Make_Spacebar,
    KEY_NONE,
};

enum Keys get_key(uint8_t bytes[2]);
