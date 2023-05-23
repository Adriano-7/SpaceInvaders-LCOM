#include <lcom/lcf.h>
#include "model/game/player.h"
#include "model/game/monster.h"
#include "model/direction.h"


void movePlayer(Player_t* player, enum Direction direction);

void moveMonsters(Monster_t* monsters[55]);

void moveMonstersY(Monster_t* monsters[55]);

void moveMonstersX(Monster_t* monsters[55]);

bool monstersCollide(Monster_t* monsters[55]);
