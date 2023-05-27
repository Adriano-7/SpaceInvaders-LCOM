#include "rtc.h"

int rtc_hook_id = 3;
Date date;

int (rtc_subscribe_int)(uint8_t *bit_no){
    if(bit_no==NULL){printf("Bit_no is a null pointer\n"); return 1;}
    *bit_no = rtc_hook_id;
  
    if(sys_irqsetpolicy(RTC_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &rtc_hook_id)){
        printf("Error subscribing the rtc\n"); 
        return 1;
    }

    return 0;
}

int (rtc_unsubscribe_int)(){
    if(sys_irqrmpolicy(&rtc_hook_id)){
        printf("Error unsubscribing the rtc\n"); 
        return 1;
    }

    return 0;
}

int (rtc_read_register)(uint8_t reg, uint8_t *data){
    if(data==NULL){printf("Data is a null pointer\n"); return 1;}

    if(sys_outb(RTC_ADDR_REG, reg)){
        printf("Error writing the register\n");
        return 1;
    }

    if(util_sys_inb(RTC_DATA_REG, data)){
        printf("Error reading the register\n");
        return 1;
    }

    return 0;
}

int (rtc_write_register)(uint8_t reg, uint8_t data){
    if(sys_outb(RTC_ADDR_REG, reg)){
        printf("Error writing the register\n");
        return 1;
    }

    if(sys_outb(RTC_DATA_REG, data)){
        printf("Error writing the data\n");
        return 1;
    }

    return 0;
}




