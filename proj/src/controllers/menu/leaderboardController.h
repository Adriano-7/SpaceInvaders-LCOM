#include <lcom/lcf.h>
#include "../keys.h"
#include "../../state.h"
#include "../../model/menu/leaderboard.h"

/**
 * @brief Handles keyboard input for the leaderboard menu.
 *
 * This function is responsible for handling keyboard input specific to the leaderboard menu.
 * It takes the pressed key as input and performs the necessary actions based on the key.
 *
 * @param key The key that was pressed.
 */
void leaderboard_handle_keyboard(enum Keys key);

/**
 * @brief Handles timer interrupt for the leaderboard menu.
 *
 * This function is responsible for handling timer interrupts specific to the leaderboard menu.
 * It performs any necessary operations that need to be executed on each timer interrupt.
 */
void leaderboard_handle_timer();
