#include "rtc.h"

uint8_t count_mode;        
int rtc_hook_id = 5; 
real_time_info time_info;   

int rtc_read_from_reg(uint8_t *output) {
   
    if (util_sys_inb(READ_REG, output) != 0){
        printf("Error reading from register\n");
        return 1;
    }
    return 0;
}

int rtc_write_to_reg(uint8_t commandWord) {
    if (sys_outb(WRITE_REG, commandWord) != 0){
        printf("Error writing to register\n");
        return 1;
    }
    return 0;
}

void start_rtc() {
    count_mode = is_binary();
    rtc_update_time();
}

int rtc_subscribe_interrupts() {
    return sys_irqsetpolicy(8, IRQ_REENABLE, &rtc_hook_id);
}

int rtc_unsubscribe_interrupts() {
    return sys_irqrmpolicy(&rtc_hook_id);
}

int is_updating() {
    uint8_t result;
    if (rtc_output(REG_UPD, &result)) return 1;
    result &= UPDATING;
	return result;
}

int rtc_output(uint8_t commandWord, uint8_t *output) {
    if(rtc_write_to_reg(commandWord)){
        printf("Error writing to register\n");
        return 1;
    };

    if(rtc_read_from_reg(output)){
        printf("Error reading from register\n");
        return 1;
    };
    return 0;}


int is_binary() {
    uint8_t result;
    if (rtc_output(REG_CNT, &result)) return 1;
	return result & BINARY;
}

int rtc_is_bcd() {
    return !is_binary();
}

uint8_t to_binary(uint8_t bcd) {
    unsigned int binary = 0;
    unsigned int factor = 1;

    while (bcd > 0) {
        unsigned int digit = bcd & 0x0F; 

        binary += digit * factor;
        factor *= 10;

        bcd >>= 4;  
    }

    return binary;
}


int rtc_update_time() {
    
    if (is_updating()) return 1;

    uint8_t output;

    if (rtc_output(S, &output)) return 1;
    if(count_mode) time_info.seconds = output;
    else time_info.seconds = to_binary(output);

    if (rtc_output(MINUTES, &output)) return 1;
    if(count_mode) time_info.minutes = output;
    else time_info.minutes = to_binary(output);

    if (rtc_output(H, &output)) return 1;
    if(count_mode) time_info.hours = output;
    else time_info.hours = to_binary(output);

    if (rtc_output(D, &output)) return 1;
    if(count_mode) time_info.day = output;
    else time_info.day = to_binary(output);

    if (rtc_output(M, &output)) return 1;
    if(count_mode) time_info.month = output;
    else time_info.month = to_binary(output);
    
    if (rtc_output(Y, &output) != 0) return 1;
    if(count_mode) time_info.year = output;
    else time_info.year = to_binary(output);

    return 0;
}
