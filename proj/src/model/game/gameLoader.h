#pragma once

#include <lcom/lcf.h>
#include "model/direction.h"
#include "../gameObject.h"
#include "player.h"
#include "monster.h"
#include "../../entities.h"

Entities_t* loadGame();

void freeGame();
