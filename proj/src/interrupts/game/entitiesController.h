#pragma once

#include "../../entities.h"
#include "../../model/game/player.h"
#include "../../model/game/monster.h"

void movePlayer(Player_t* player, enum Direction direction);

bool monstersCollide(Monster_t* monsters[55]);

void moveMonsters(Monster_t* monsters[55]);

void moveMonstersX(Monster_t* monsters[55]);

void moveMonstersY(Monster_t* monsters[55]);

