#include <lcom/lcf.h>
#include <stdint.h>

#include "keyboard.h"

uint8_t output;
int keyboard_hook_id = 1;

int (keyboard_subscribe_interrupts)(uint8_t *bit_no){
  if(bit_no == NULL){printf("bit_no is nullptr\n"); return 1;}
  *bit_no = BIT(keyboard_hook_id);
    
  if(sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_ENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id)){
    printf("Error setting irq policy for the keyboard\n");
    return 1;
  }
  return 0;
}

int (keyboard_unsubscribe_interrupts)(){
  if(sys_irqrmpolicy(&keyboard_hook_id)){
    printf("Error removing policy for the keyboard\n");
    return 1;
  }
  return 0;
}

void (kbc_ih)(){
  read_KBC_output(KBC_OUT_CMD, &output);
}

int (keyboard_restore)(){
  uint8_t commandByte;

  if(write_KBC_command(KBC_IN_CMD, KBC_READ_CMD)) {
    printf("Error writing Read Command Byte\n"); 
    return 1;
  }

  if(read_KBC_output(KBC_OUT_CMD, &commandByte)){
    printf("Error Reading Command Byte\n"); 
    return 1;
  }

  commandByte |= ENABLE_INT;

  if(write_KBC_command(KBC_IN_CMD, KBC_WRITE_CMD)){
    printf("Error writing Write Command Byte\n"); 
    return 1;
  }

  if(write_KBC_command(KBC_OUT_CMD, commandByte)){
    printf("Error writing the new command byte\n");
    return 1;
  }
  
  return 0;
}
