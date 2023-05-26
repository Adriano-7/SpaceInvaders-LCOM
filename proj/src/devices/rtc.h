#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "rtc_macros.h"

// Estrutura que reune todos os dados importantes
typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t year;
    uint8_t month;
    uint8_t day;
} real_time_info;

// Functions
void start_rtc();
int rtc_subscribe_interrupts();
int rtc_unsubscribe_interrupts();
int rtc_write_to_reg(uint8_t commandWord);
int rtc_read_from_reg(uint8_t *output);
int rtc_output(uint8_t commandWord, uint8_t *output);
int is_updating();
int is_binary();
int rtc_update_time();
uint8_t to_binary(uint8_t bcd);

#endif
