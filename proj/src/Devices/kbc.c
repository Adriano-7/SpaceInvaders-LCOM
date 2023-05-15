#include <lcom/lcf.h>

#include <stdint.h>

#include "kbc.h"
#include "i8042.h"

int (read_KBC_status)(uint8_t* status){
    if(util_sys_inb(KBC_STATUS_REG, status)){
        printf("Error reading the status\n");
        return 1;
    }
    return 0;
}

int (read_KBC_output)(uint8_t port, uint8_t *output){
    int attempts = 10;
    uint8_t status;

    while(attempts){
        if(read_KBC_status(&status)){
            printf("Error reading the status\n");
            return 1;
        }
        if(status & FULL_OUT_BUFFER){
            if(util_sys_inb(port, output)){
                printf("Error reading the output\n");
                return 1;
            }
            return 0;
        }
        tickdelay(micros_to_ticks(20000));
        attempts--;
    }

    printf("Error reading the output\n");
    return 1;
}

int (write_KBC_command)(uint8_t port, uint8_t commandByte){
    int attempts = 10;
    uint8_t status;

    while(attempts){
        if(read_KBC_status(&status)){
            printf("Error reading the status\n");
            return 1;
        }
        if(!(status & !FULL_IN_BUFFER)){
            if(sys_outb(port, commandByte)){
                printf("Error writing the command byte\n");
                return 1;
            }
            return 0;
        }
        tickdelay(micros_to_ticks(20000));
        attempts--;
    }

    printf("Error writing the command byte\n");
    return 1;
}
