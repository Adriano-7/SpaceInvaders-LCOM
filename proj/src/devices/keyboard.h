/**
 * @file keyboard.h
 * @brief Functions and constants for handling the keyboard.
 */

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

/**
 * @brief Subscribes to keyboard interrupts.
 *
 * @param bit_no Address of memory to store the hook_id bit number.
 * @return Return 0 upon success, non-zero otherwise.
 */
int keyboard_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes from keyboard interrupts.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int keyboard_unsubscribe_int();

/**
 * @brief Gets the keyboard status.
 *
 * @param st Address of memory to store the keyboard status.
 * @return Return 0 upon success, non-zero otherwise.
 */
int keyboard_get_status(uint8_t *st);

/**
 * @brief Keyboard interrupt handler.
 */
void keyboard_int_handler();

/**
 * @brief Parses the keyboard output.
 *
 * @return True if parsing was successful, false otherwise.
 */
bool keyboard_parse_output();
