#include <lcom/lcf.h>
#include <stdint.h>

#include "mouse.h"

int mouse_hook_id = IRQ_MOUSE;
uint8_t output;

int (mouse_subscribe_interrupts)(uint8_t *bit_no){
  if(bit_no == NULL){printf("bit_no is nullptr\n"); return 1;}
  *bit_no = BIT(mouse_hook_id);
    
  if(sys_irqsetpolicy(IRQ_MOUSE, IRQ_ENABLE | IRQ_EXCLUSIVE, &mouse_hook_id)){
    printf("Error setting irq policy for the mouse\n");
    return 1;
  }
  return 0;
}

int (mouse_unsubscribe_interrupts)(){
  if(sys_irqrmpolicy(mouse_hook_id)){
    printf("Error removing irq policy for the mouse\n");
    return 1;
  }
  return 0;
}

void (mouse_ih)(){
  read_KBC_output(KBC_OUT_CMD, &output, 1);
}

uint8_t byte_index = 0;       // [0..2]
uint8_t packet[3];            // pacote
uint8_t current_byte;         // o byte mais recente lido

void mouse_sync_bytes(){

}