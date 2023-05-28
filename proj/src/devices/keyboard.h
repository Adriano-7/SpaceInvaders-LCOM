#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

int (keyboard_subscribe_int)(uint8_t *bit_no);

int (keyboard_unsubscribe_int)();

/**
 * @brief Construct a new int object.
 * 
 */
int (keyboard_get_status(uint8_t *st));

void (keyboard_int_handler)();

/**
 * @brief Keybord Parse Output.
 * 
 * @return true 
 * @return false 
 */
bool keyboard_parse_output();

#endif

