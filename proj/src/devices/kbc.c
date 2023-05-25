#include <lcom/lcf.h>

#include <stdint.h>

#include "kbc.h"
#include "i8042.h"

uint8_t output;

int (read_KBC_status)(uint8_t* status){
    if(util_sys_inb(KBC_STATUS_REG, status)){
        printf("Error reading the status\n");
        return 1;
    }
    return 0;
}

int (read_KBC_output)(uint8_t port, uint8_t *output, uint8_t mouse){
  if(output==NULL){printf("output is nullptr\n"); return 1;}

  uint8_t st;
  uint8_t attempts = MAX_TRIES;

  while(attempts){
    if(read_KBC_status(&st)){
      printf("An error has occured while reading the status\n");
      return 1;
    }

    if(st & FULL_OUT_BUFFER){
      if(util_sys_inb(port, output)){
        printf("Error while using sys_inb\n");
        return 1;
      }
      
      if(st & PARITY_ERROR){
        printf("Parity Error has occurred\n");
        return 1;
      }

      if(st & TIMEOUT_ERROR){
        printf("Timed out error has occured\n");
        return 1;
      }

      if (mouse && !(st & AUX)) {
        printf("Error: Mouse output not found\n");
        return 1;
      } 
      if (!mouse && (st & AUX)) {
        printf("Error: Keyboard output not found\n");
        return 1;
      } 
      return 0;
    }

    tickdelay(micros_to_ticks(20000));
    attempts--;
  }

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
