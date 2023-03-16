#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc.h"

int (mouse_subscribe_interrupts)(uint8_t *bit_no);

int (mouse_unsubscribe_interrupts)();

void(mouse_ih)();