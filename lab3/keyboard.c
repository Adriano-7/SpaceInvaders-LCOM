#include "keyboard.h"

int keyboard_hook_id = 1;
uint8_t scancode;

uint8_t kbd_bytes[2];
int kbd_bytesCounter = 0;

int (keyboard_subscribe_int)(uint8_t *bit_no){
    if(bit_no==NULL){printf("Bit_no is a null pointer\n"); return 1;}
    *bit_no = keyboard_hook_id;
  
    if(sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id)){
      printf("Error subscribing the keyboard\n"); 
      return 1;
    }

    return 0;
}

int (keyboard_unsubscribe_int)(){
    if(sys_irqrmpolicy(&keyboard_hook_id)){
      printf("Error unsubscribing the keyboard\n"); 
      return 1;
    }

    return 0;
}

int (keyboard_get_status(uint8_t *st)){
    if(st==NULL){printf("Status is a null pointer\n"); return 1;}
    if(util_sys_inb(KEYBOARD_ST_REG, st)){
        printf("Error reading the status\n"); 
        return 1;
    }
    return 0;
}

void (keyboard_int_handler)(){
    uint8_t status;
    if(keyboard_get_status(&status)){
        printf("Error reading the status\n");
        return;
    }

    if(status & KEYBOARD_ST_PARITY || status & KEYBOARD_ST_TIMEOUT){
        printf("Error in the communication\n");
        return;
    }

    if(status & KEYBOARD_ST_OBF){
        if(util_sys_inb(KEYBOARD_OUT_BUF, &scancode)){
            printf("Error reading the scancode\n");
            return;
        }
    }

    return;
}

bool keyboard_parse_output(){
    if(kbd_bytesCounter == 0){
        kbd_bytes[0] = scancode;
        if(scancode == KEYBOARD_TWO_BYTE){
            kbd_bytesCounter++;
            return false;
        }
        else{
            kbd_bytesCounter = 0;
            return true;
        }
    }
    else{
        kbd_bytes[1] = scancode;
        kbd_bytesCounter = 0;
        return true;
    }

    return false;
}
