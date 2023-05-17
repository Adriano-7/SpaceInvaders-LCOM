#include <lcom/lcf.h>
#include <stdint.h>

#include "mouse.h"

int mouse_hook_id = 4;
struct packet pp;

uint8_t byte_index = 0;
uint8_t packet[3];
extern uint8_t output;

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
  if(sys_irqrmpolicy(&mouse_hook_id)){
    printf("Error removing irq policy for the mouse\n");
    return 1;
  }
  return 0;
}

void (mouse_ih)(){
  read_KBC_output(KBC_OUT_CMD, &output, 1);
}

bool mouse_parse_output(){
  switch(byte_index){
    case 0:
      if((output & MOUSE_FIRST_BYTE) == 0){
        return false;
      }
      packet[byte_index] = output;
      byte_index++;
      break;

    case 1:
      packet[byte_index] = output;
      byte_index++;
      break;

    case 2:
      packet[byte_index] = output;
      byte_index = 0;
      return true;
      break;
  }
  return false;
}

void mouse_build_packet(){
  for(int i = 0; i < 3; i++){
    pp.bytes[i] = packet[i];
  }

  pp.lb = (packet[0] & MOUSE_LB);
  pp.rb = (packet[0] & MOUSE_RB) >> 1;
  pp.mb = (packet[0] & MOUSE_MB) >> 2;

  pp.delta_x =  twoComplement(&packet[1], (packet[0] & MOUSE_X_OVF));
  pp.delta_y =  twoComplement(&packet[2], (packet[0] & MOUSE_Y_OVF));

  pp.x_ov = (packet[0] & MOUSE_X_OVF);
  pp.y_ov = (packet[0] & MOUSE_Y_OVF);
}

int write_mouse_cmd(uint8_t cmd){
  uint8_t ack;
  uint8_t tries = 0;

  do{
    if(write_KBC_command(KBC_IN_CMD, MOUSE_WRITE_BYTE)){
      printf("Error writing mouse command\n");
      return 1;
    }

    if(write_KBC_command(KBC_OUT_CMD, cmd)){
      printf("Error writing mouse command\n");
      return 1;
    }

    tickdelay(micros_to_ticks(KBC_DELAY));

    if(util_sys_inb(KBC_OUT_CMD, &ack)){
      printf("Error reading mouse command ack\n");
      return 1;
    }

    if(ack == MOUSE_ACK){return 0;}
    if(ack == MOUSE_NACK){tries++; continue;}

  } while(tries < MAX_TRIES);

  printf("Error writing mouse command\n");
  return 1;
}

int enable_data_report(){
  return write_mouse_cmd(MOUSE_ENABLE_DATA_REPORTING);
}

int disable_data_report(){
  return write_mouse_cmd(MOUSE_DISABLE_DATA_REPORTING);
}

uint16_t twoComplement(uint8_t* number, uint8_t overflow){
  if(overflow){
    return (uint16_t) (0xFF00 | *number); 
  }
  return (uint16_t) (0x0000 | *number);
}
