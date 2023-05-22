#include <lcom/lcf.h>
#include "../state.h"

#include "keys.h"
#include "model/game/player.h"
#include "model/direction.h"
#include "model/menu/menu.h"

#include "game/gameController.h"
#include "model/game/player.h"
#include "../map.h"

int (handle_keyboard)(enum State* state, uint8_t bytes[2], Player_t* player);

int (handle_timer)(enum State* state, Map_t *map, Menu_t* menu);
