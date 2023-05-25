#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc.h"

int (mouse_subscribe_interrupts)(uint8_t *bit_no);

int (mouse_unsubscribe_interrupts)();

void(mouse_ih)();

bool mouse_parse_output();

void mouse_build_packet();

int write_mouse_cmd(uint8_t cmd);

int disable_data_report();

int enable_data_report();

uint16_t twoComplement(uint8_t* number, uint8_t msb);
