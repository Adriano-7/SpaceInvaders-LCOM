#include <lcom/lcf.h>
#include <stdint.h>

#include "../headers/devices/keyboard.h"

int keyboard_hook_id=1;
uint8_t output = 0;

int (keyboard_subscribe_interrupts)(uint8_t *bit_no){
    *bit_no = keyboard_hook_id;
    if(sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id)){
        printf("keyboard_subscribe_interrupts() -> Error setting policy for keyboard interrupts\n");
        return 1;
    }
    
    return 0;
}

int (keyboard_unsubscribe_interrupts)(){
    if(sys_irqrmpolicy(&keyboard_hook_id)){
        printf("Error removing policy for keyboard interrupts");
        return 1;
    }
    return 0;
}

void (kbc_ih)(){
    util_sys_inb(KBC_OUT_BUF, &output);
}

int (keyboard_restore)(){
    if(sys_outb(0x64, 0x20)){
        printf("Error writing command 'Write Command Byte' to KBC");
        return 1;
    }

    uint8_t commandByte;
    if(util_sys_inb(0x60, &commandByte)){
        printf("Error reading command byte from KBC");
        return 1;
    }

    commandByte |= 0x01; //enable keyboard interrupts

    if(sys_outb(0x64, 0x60)){
        printf("Error writing new command byte to KBC");
        return 1;
    }

    if(sys_outb(0x64, 0xAE)){
        printf("Error writing command 'Enable Scanning' to KBC");
        return 1;
    }

    return 0;
}
