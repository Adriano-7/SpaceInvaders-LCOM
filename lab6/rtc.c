#include "rtc.h"

int rtc_hook_id = 3;
Date_t date;

uint8_t regA, regB, regC, regD;

int (rtc_subscribe_int)(uint8_t *bit_no){
    if(bit_no==NULL){printf("Bit_no is a null pointer\n"); return 1;}
    *bit_no = rtc_hook_id;
  
    if(sys_irqsetpolicy(RTC_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &rtc_hook_id)){
        printf("Error subscribing the rtc\n"); 
        return 1;
    }

    if(rtc_startup()){
        printf("Error starting up the UIE interrupts\n");
        return 1;
    }

    return 0;
}

int (rtc_unsubscribe_int)(){
    if(sys_irqrmpolicy(&rtc_hook_id)){
        printf("Error unsubscribing the rtc\n"); 
        return 1;
    }

    if(rtc_startdown()){
        printf("Error disabiling the UIE interrupts\n");
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

    rtc_convert_bcd(data);

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

int (rtc_startup)(){
    if(rtc_read_register(RTC_REG_B, &regB)){
        printf("Error reading register B\n");
        return 1;
    }

    regB |= RTC_B_UIE_BIT;

    if(rtc_write_register(RTC_REG_B, regB)){
        printf("Error writing register B\n");
        return 1;
    }

    return 0;
}

int (rtc_startdown)(){
    if(rtc_read_register(RTC_REG_B, &regB)){
        printf("Error reading register B\n");
        return 1;
    }

    regB &= ~RTC_B_UIE_BIT;

    if(rtc_write_register(RTC_REG_B, regB)){
        printf("Error writing register B\n");
        return 1;
    }

    return 0;
}

int (rtc_convert_bcd)(uint8_t *data){
    if(data==NULL){printf("Data is a null pointer\n"); return 1;}

    *data = (*data >> 4) * 10 + (*data & 0x0F);

    return 0;
}

int (rtc_update_date)(){
    regA = 0;

    while (regA & RTC_A_UIP_BIT) {
        if(rtc_read_register(RTC_REG_A, &regA)){
            printf("Error reading register A\n");
            return 1;
        }
    }

    if(rtc_read_register(RTC_REG_SECONDS, &date.seconds)){
        printf("Error reading seconds\n");
        return 1;
    }

    if(rtc_read_register(RTC_REG_MINUTES, &date.minutes)){
        printf("Error reading minutes\n");
        return 1;
    }

    if(rtc_read_register(RTC_REG_HOURS, &date.hours)){
        printf("Error reading hours\n");
        return 1;
    }

    if(rtc_read_register(RTC_REG_DAY_MONTH, &date.day)){
        printf("Error reading day\n");
        return 1;
    }

    if(rtc_read_register(RTC_REG_MONTH, &date.month)){
        printf("Error reading month\n");
        return 1;
    }

    if(rtc_read_register(RTC_REG_YEAR, &date.year)){
        printf("Error reading year\n");
        return 1;
    }
    return 0;
}

void (rtc_int_handler)(){
    if(rtc_read_register(RTC_REG_C, &regC)){
        printf("Error reading register C\n");
        return;
    }

    if(regC & RTC_C_UF_BIT){
        if(rtc_update_date()){
            printf("Error updating the date\n");
            return;
        }
    }
}
