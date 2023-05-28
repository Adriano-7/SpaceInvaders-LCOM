#include <lcom/lcf.h>
#include "../../state.h"

#include "../keys.h"

#include "model/menu/menu.h"
#include "../../state.h"

extern struct packet pkt;

/**
 * @brief Handles keyboard input for the menu.
 *
 * This function is responsible for handling keyboard input specific to the menu.
 * It takes the pressed key as input and performs the necessary actions based on the key.
 *
 * @param key The key that was pressed.
 */
void menu_handle_keyboard(enum Keys key);

/**
 * @brief Handles timer interrupt for the menu.
 *
 * This function is responsible for handling timer interrupts specific to the menu.
 * It performs any necessary operations that need to be executed on each timer interrupt.
 *
 * @param menu Pointer to the menu structure.
 */
void menu_handle_timer();

/**
 * @brief Handles mouse input for the menu.
 *
 * This function is responsible for handling mouse input specific to the menu.
 * It takes the mouse packet as input and performs the necessary actions based on the packet.
 *
 * @param menu Pointer to the menu structure.
 */
void menu_handle_mouse();

/**
 * @brief Selects an option in the menu based on the mouse input.
 *
 * This function is responsible for selecting an option in the menu based on the mouse input.
 * It takes the menu structure and the mouse packet as input and performs the necessary actions
 * to select the corresponding option.
 *
 * @param menu Pointer to the menu structure.
 * @param pp The mouse packet.
 */
void selectOption();
