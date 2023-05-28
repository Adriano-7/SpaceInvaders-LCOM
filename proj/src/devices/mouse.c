#include "mouse.h"

int mouse_hook_id = 4;

uint8_t mouse_out;

uint8_t mouse_bytes[3];
int mouse_bytesIndex = 0;
struct packet pkt;

int (mouse_subscribe_int)(uint8_t *bit_no){
    if(bit_no == NULL){printf("bit_no is nullptr\n"); return 1;}
    *bit_no = mouse_hook_id;

    if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != OK){
        printf("Error setting mouse interrupts\n");
        return 1;
    }
    return 0;
}

int (mouse_unsubscribe_int)(){
    if(sys_irqrmpolicy(&mouse_hook_id)){
        printf("Error removing mouse interrupts\n");
        return 1;
    }
    return 0;
}

int (mouse_get_status(uint8_t *st)){
    if(st == NULL){printf("st is nullptr\n"); return 1;}
    if(util_sys_inb(MOUSE_ST_REG, st)){
        printf("Error reading the status\n");
        return 1;
    }
    return 0;
}

void(mouse_ih)(){
    uint8_t status;
    int attempts = 10;

    while(attempts--){
        mouse_get_status(&status);
        if(status & MOUSE_ST_OBF){
            if(util_sys_inb(MOUSE_OUT_BUF, &mouse_out)){
                printf("Error reading the scancode\n");
                return;
            }

            if(status & MOUSE_ST_PARITY){
                printf("Parity error\n");
                return;
            }

            if(status & MOUSE_ST_TIMEOUT){
                printf("Timeout error\n");
                return;
            }

            if(status & MOUSE_ST_AUX){
                printf("Mouse output not found\n");
                return;
            }
                
            break;
        }

        tickdelay(micros_to_ticks(20000));
    }

    return;
}

bool mouse_parse_output(){
  switch(mouse_bytesIndex){
    case 0:
      if((mouse_out & MOUSE_FIRST_BYTE) == 0){
        return false;
      }
      mouse_bytes[mouse_bytesIndex] = mouse_out;
      mouse_bytesIndex++;
      break;

    case 1:
      mouse_bytes[mouse_bytesIndex] = mouse_out;
      mouse_bytesIndex++;
      break;

    case 2:
      mouse_bytes[mouse_bytesIndex] = mouse_out;
      mouse_bytesIndex = 0;
      return true;
      break;
  }
  return false;
}

uint16_t twoComplement(uint8_t* number, uint8_t msb){
  return (msb) ? (uint16_t) (0xFF00 | *number) : (uint16_t) (0x0000 | *number);
}

void mouse_build_packet(){
  for(int i = 0; i < 3; i++){
    pkt.bytes[i] = mouse_bytes[i];
  }

  pkt.lb = (mouse_bytes[0] & MOUSE_LEFT_BUTTON);
  pkt.rb = (mouse_bytes[0] & MOUSE_RIGHT_BUTTON) >> 1;
  pkt.mb = (mouse_bytes[0] & MOUSE_MIDDLE_BUTTON) >> 2;

  pkt.delta_x =  twoComplement(&mouse_bytes[1], (mouse_bytes[0] & MOUSE_X_MSB));
  pkt.delta_y =  twoComplement(&mouse_bytes[2], (mouse_bytes[0] & MOUSE_Y_MSB));

  pkt.x_ov = (mouse_bytes[0] & MOUSE_X_OVF);
  pkt.y_ov = (mouse_bytes[0] & MOUSE_Y_OVF);
}

int write_KBC_command(uint8_t port, uint8_t cmd){
    uint8_t status;
    int attempts = 10;
    while(attempts--){
        if(mouse_get_status(&status)){
            printf("Error reading the status\n");
            return 1;
        }

        if((status & MOUSE_ST_IBF) == 0){
            if(sys_outb(port, cmd)){
                printf("Error writing the command\n");
                return 1;
            }
            return 0;
        }

        tickdelay(micros_to_ticks(20000));
    }

    return 1;
}

int write_mouse_cmd(uint8_t cmd){
  uint8_t ack;

  for(int attempts=0; attempts<100; attempts++){
    if(write_KBC_command(KBC_IN_CMD, MOUSE_WRITE_BYTE)){
      printf("Error writing mouse command\n");
      return 1;
    }

    if(write_KBC_command(KBC_OUT_CMD, cmd)){
      printf("Error writing mouse command\n");
      return 1;
    }

    tickdelay(micros_to_ticks(20000));

    if(util_sys_inb(KBC_OUT_CMD, &ack)){
      printf("Error reading mouse command ack\n");
      return 1;
    }

    if(ack == MOUSE_ACK){return 0;}
    if(ack == MOUSE_NACK){attempts++; continue;}

  }

  printf("Error writing mouse command\n");
  return 1;
}

int disable_data_report(){
  return write_mouse_cmd(MOUSE_DISABLE_DATA_REPORTING);
}

int enable_data_report(){
  return write_mouse_cmd(MOUSE_ENABLE_DATA_REPORTING);
}

