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

#include "../../state.h"

/**
 * @brief Handles keyboard input during the game.
 * @param key The key that was pressed.
 * @param map Pointer to the game map.
 *
 * This function is responsible for handling keyboard input during the game. It takes the key that was pressed
 * as input and updates the game state accordingly. The map parameter is a pointer to the game map, which is
 * used to update the player's movement or perform other actions based on the key input.
 */
void (game_handle_keyboard)(enum Keys key);

/**
 * @brief Handles timer interrupts during the game.
 * @param map Pointer to the game map.
 *
 * This function is called on every timer interrupt during the game. It updates the game state based on the
 * elapsed time. The map parameter is a pointer to the game map, which is used to update the game entities
 * and perform other time-dependent operations.
 */
void (game_handle_timer)();
