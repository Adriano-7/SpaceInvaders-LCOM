#include "rtc.h"

uint8_t count_mode;        
int rtc_hook_id = 5; 
real_time_info time_info;   

void start_rtc() {
    count_mode = rtc_is_binary();
    rtc_update_time();
}

int rtc_subscribe_interrupts() {
    return sys_irqsetpolicy(8, IRQ_REENABLE, &rtc_hook_id);
}

int rtc_unsubscribe_interrupts() {
    return sys_irqrmpolicy(&rtc_hook_id);
}

// Leitura do output do RTC, dado um comando
int rtc_output(uint8_t command, uint8_t *output) {
    if (sys_outb(REG_INPUT, command) != 0) return 1;
	if (util_sys_inb(REG_OUTPUT, output) != 0) return 1;
    return 0;
}

// Retorna 1 se naquele momento o RTC está a atualizar os seus valores internos
// Nesse caso não devemos ler nenhum registo
int rtc_is_updating() {
    uint8_t result;
    if (rtc_output(REG_UPD, &result)) return 1;
	return result & UPDATING;
}

// Retorna 1 se o modo de contagem for binário
int rtc_is_binary() {
    uint8_t result;
    if (rtc_output(REG_CNT, &result)) return 1;
	return result & BINARY;
}

// Retorna 1 se o modo de contagem for BCD
int rtc_is_bcd() {
    return !rtc_is_binary();
}

// Transforma um valor de 8 bits BCD em binário
uint8_t to_binary(uint8_t bcd_number) {
    return ((bcd_number >> 4) * 10) + (bcd_number & 0xF);
}

int rtc_update_time() {
    
    // Se o RTC estiver ocupado a atualizar os registos não devemos ler dados
    if (rtc_is_updating() != 0) return 1;
    uint8_t output;

    // Seconds
    if (rtc_output(S, &output) != 0) return 1;
    time_info.seconds = count_mode ? output : to_binary(output);

    // Minutes
    if (rtc_output(MINUTES, &output) != 0) return 1;
    time_info.minutes = count_mode ? output : to_binary(output);

    // Hours
    if (rtc_output(H, &output) != 0) return 1;
    time_info.hours = count_mode ? output : to_binary(output);

    // Day
    if (rtc_output(D, &output) != 0) return 1;
    time_info.day = count_mode ? output : to_binary(output);

    // Month
    if (rtc_output(M, &output) != 0) return 1;
    time_info.month = count_mode ? output : to_binary(output);

    // Year
    if (rtc_output(Y, &output) != 0) return 1;
    time_info.year = count_mode ? output : to_binary(output);

    return 0;
}
