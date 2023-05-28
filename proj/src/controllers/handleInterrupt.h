#include <lcom/lcf.h>
#include "../state.h"

#include "keys.h"
#include "model/game/player.h"
#include "model/direction.h"

#include "game/gameController.h"
#include "menu/menuController.h"
#include "menu/leaderboardController.h"

int (handle_keyboard)(enum State* state);

int (handle_timer)(enum State* state);

int (handle_mouse)(enum State* state);
