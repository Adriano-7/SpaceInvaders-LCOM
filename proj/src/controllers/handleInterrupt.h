#include <lcom/lcf.h>
#include "../state.h"

#include "keys.h"
#include "model/game/player.h"
#include "model/direction.h"

#include "game/gameController.h"
#include "menu/menuController.h"
#include "menu/leaderboardController.h"

#include "model/game/player.h"
#include "../model/game/map.h"
#include "../model/menu/menu.h"

int (handle_keyboard)(enum State* state, Map_t* map, Menu_t* menu);

int (handle_timer)(enum State* state, Map_t *map, Menu_t* menu);

int (handle_mouse)(enum State* state, Map_t* map, Menu_t* menu);
