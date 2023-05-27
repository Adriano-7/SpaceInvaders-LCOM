#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

int (keyboard_subscribe_int)(uint8_t *bit_no);

int (keyboard_unsubscribe_int)();

int (keyboard_get_status(uint8_t *st));

void (keyboard_int_handler)();

bool keyboard_parse_output();

#endif

