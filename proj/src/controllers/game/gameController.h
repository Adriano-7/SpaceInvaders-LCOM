#include <lcom/lcf.h>
#include "../../state.h"

#include "../keys.h"
#include "model/game/player.h"
#include "model/direction.h"

#include "model/game/player.h"
#include "../../model/game/map.h"
#include "../../xpm/loadXpm.h"

#include "entities/monsterController.h"
#include "entities/playerController.h"
#include "entities/bulletController.h"

extern int timer_counter;

void (game_handle_keyboard)(enum Keys key, Map_t* map);

void (game_handle_timer)(Map_t* map);

