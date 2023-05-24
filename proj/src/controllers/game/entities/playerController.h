#include <lcom/lcf.h>
#include "model/game/player.h"
#include "model/game/map.h"
#include "model/direction.h"

extern vbe_mode_info_t mode_info;

void movePlayer(Player_t* player, enum DirectionX direction);
