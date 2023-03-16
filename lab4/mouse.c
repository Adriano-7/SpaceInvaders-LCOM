#include <lcom/lcf.h>
#include <stdint.h>

#include "mouse.h"

int mouse_hook_id = IRQ_MOUSE;
extern output;

uint8_t byte_index = 0;       // [0..2]
uint8_t packet[3];            // pacote
uint8_t current_byte;         // o byte mais recente lido

int (mouse_subscribe_interrupts)(uint8_t *bit_no){
}

int (mouse_unsubscribe_interrupts)(){
}

void (mouse_ih)(){
  return kbc_ih(1);
}