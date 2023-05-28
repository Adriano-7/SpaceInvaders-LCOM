#include <lcom/lcf.h>
#include "../state.h"

#include "keys.h"
#include "model/game/player.h"
#include "model/direction.h"

#include "game/gameController.h"
#include "menu/menuController.h"
#include "menu/leaderboardController.h"
#include "menu/gameOverController.h"
/**
 * @brief Handles keyboard input for the game.
 *
 * This function is responsible for handling keyboard input in the game.
 * It takes the current state, keyboard input bytes, map, menu, and game over menu as input,
 * and performs the necessary actions based on the input.
 *
 * @param state Pointer to the current state.
 * @return Return 0 on success, non-zero otherwise.
 */
int (handle_keyboard)(enum State* state);

/**
 * @brief Handles timer interrupt for the game.
 *
 * This function is responsible for handling timer interrupts in the game.
 * It takes the current state, game map, menu, and game over menu as input,
 * and performs any necessary operations that need to be executed on each timer interrupt.
 *
 * @param state Pointer to the current state.
 * @return Return 0 on success, non-zero otherwise.
 */
int handle_timer(enum State* state);

/**
 * @brief Handles mouse input for the game.
 *
 * This function is responsible for handling mouse input in the game.
 * It takes the current state, game map, menu, and game over menu as input,
 * and performs the necessary actions based on the mouse input.
 *
 * @param state Pointer to the current state.
 * @return Return 0 on success, non-zero otherwise.
 */
int handle_mouse(enum State* state);

int (handle_keyboard)(enum State* state);

int (handle_timer)(enum State* state);

int (handle_mouse)(enum State* state);
