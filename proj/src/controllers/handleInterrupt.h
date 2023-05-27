#include <lcom/lcf.h>
#include "../state.h"

#include "keys.h"
#include "model/game/player.h"
#include "model/direction.h"

#include "game/gameController.h"
#include "menu/menuController.h"
#include "menu/leaderboardController.h"
#include "menu/overController.h"

#include "model/game/player.h"
#include "../model/game/map.h"
#include "../model/menu/menu.h"
#include "../model/menu/over.h"

/**
 * @brief Handles keyboard input for the game.
 *
 * This function is responsible for handling keyboard input in the game.
 * It takes the current state, keyboard input bytes, map, menu, and game over menu as input,
 * and performs the necessary actions based on the input.
 *
 * @param state Pointer to the current state.
 * @param bytes Array containing the keyboard input bytes.
 * @param map Pointer to the game map structure.
 * @param menu Pointer to the menu structure.
 * @param over Pointer to the game over menu structure.
 * @return Return 0 on success, non-zero otherwise.
 */
int handle_keyboard(enum State* state, uint8_t bytes[2], Map_t* map, Menu_t* menu, Over_t* over);

/**
 * @brief Handles timer interrupt for the game.
 *
 * This function is responsible for handling timer interrupts in the game.
 * It takes the current state, game map, menu, and game over menu as input,
 * and performs any necessary operations that need to be executed on each timer interrupt.
 *
 * @param state Pointer to the current state.
 * @param map Pointer to the game map structure.
 * @param menu Pointer to the menu structure.
 * @param over Pointer to the game over menu structure.
 * @return Return 0 on success, non-zero otherwise.
 */
int handle_timer(enum State* state, Map_t* map, Menu_t* menu, Over_t* over);

/**
 * @brief Handles mouse input for the game.
 *
 * This function is responsible for handling mouse input in the game.
 * It takes the current state, game map, menu, and game over menu as input,
 * and performs the necessary actions based on the mouse input.
 *
 * @param state Pointer to the current state.
 * @param map Pointer to the game map structure.
 * @param menu Pointer to the menu structure.
 * @param over Pointer to the game over menu structure.
 * @return Return 0 on success, non-zero otherwise.
 */
int handle_mouse(enum State* state, Map_t* map, Menu_t* menu, Over_t* over);
