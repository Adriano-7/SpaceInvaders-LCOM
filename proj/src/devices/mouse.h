#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "macros.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

int (mouse_get_status(uint8_t *st));

void(mouse_ih)();

bool mouse_parse_output();

uint16_t twoComplement(uint8_t* number, uint8_t msb);

void mouse_build_packet();

int write_KBC_command(uint8_t port, uint8_t cmd);

int write_mouse_cmd(uint8_t cmd);

int disable_data_report();

int enable_data_report();

