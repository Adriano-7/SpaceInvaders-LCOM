#include <lcom/lcf.h>
#include "../../state.h"

#include "../keys.h"
#include "model/game/player.h"
#include "model/direction.h"

#include "model/game/player.h"
#include "../../map.h"
#include "../../xpm/loadXpm.h"

void (game_handle_keyboard)(enum Keys key, Player_t* player);

void (game_handle_timer)(Map_t* map);

void movePlayer(Player_t* player, enum Direction direction);

bool monstersCollide(Monster_t* monsters[55]);

void moveMonsters(Monster_t* monsters[55]);

void moveMonstersX(Monster_t* monsters[55]);

void moveMonstersY(Monster_t* monsters[55]);
