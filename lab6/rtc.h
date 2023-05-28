#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

int (rtc_subscribe_int)(uint8_t *bit_no);

int (rtc_unsubscribe_int)();

int (rtc_read_register)(uint8_t reg, uint8_t *data);

int (rtc_write_register)(uint8_t reg, uint8_t data);

int (rtc_startup)();

int (rtc_startdown)();

int (rtc_convert_bcd)(uint8_t *data);

int (rtc_update_date)();

void (rtc_int_handler)();

typedef struct Date{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
} Date_t;

#endif

