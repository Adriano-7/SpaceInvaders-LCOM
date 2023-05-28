#include <lcom/lcf.h>
#include "../../state.h"

#include "../keys.h"

#include "model/menu/gameOver.h"
#include "../../state.h"

extern struct packet pp;

/**
 * @brief Handles keyboard input for the game over menu.
 *
 * This function is responsible for handling keyboard input specific to the game over menu.
 * It takes the pressed key as input and performs the necessary actions based on the key.
 *
 * @param key The key that was pressed.
 */
void game_over_handle_keyboard(enum Keys key);

/**
 * @brief Handles timer interrupt for the game over menu.
 *
 * This function is responsible for handling timer interrupts specific to the game over menu.
 * It performs any necessary operations that need to be executed on each timer interrupt.
 *
 * @param over Pointer to the game over menu structure.
 */
void game_over_handle_timer();

/**
 * @brief Handles mouse input for the game over menu.
 *
 * This function is responsible for handling mouse input specific to the game over menu.
 * It takes the mouse packet as input and performs the necessary actions based on the packet.
 *
 * @param over Pointer to the game over menu structure.
 */
void game_over_handle_mouse();

/**
 * @brief Selects an option in the game over menu based on the mouse input.
 *
 * This function is responsible for selecting an option in the game over menu based on the mouse input.
 * It takes the game over menu structure and the mouse packet as input and performs the necessary actions
 * to select the corresponding option.
 *
 * @param over Pointer to the game over menu structure.
 * @param pp The mouse packet.
 */
void game_over_option();
