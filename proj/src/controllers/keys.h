#pragma once
#include <lcom/lcf.h>
#include <stdint.h>

#include "../devices/macros.h"

enum Keys {
    Make_Arrow_left,
    Make_Arrow_right,
    Make_Spacebar,
    Make_Esc,
    KEY_NONE,
};

enum Keys get_key(uint8_t bytes[2]);
