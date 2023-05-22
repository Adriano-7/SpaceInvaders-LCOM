#pragma once

#include <lcom/lcf.h>
#include "model/direction.h"
#include "../gameObject.h"
#include "player.h"
#include "monster.h"
#include "../../map.h"

Map_t* loadGame();

void freeGame();
