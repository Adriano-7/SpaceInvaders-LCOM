/**
 * @file rtc.h
 * @brief Functions and constants for handling the Real-Time Clock (RTC).
 */

#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

/**
 * @brief Subscribes to RTC interrupts.
 *
 * @param bit_no Address of memory to store the hook_id bit number.
 * @return Return 0 upon success, non-zero otherwise.
 */
int rtc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes from RTC interrupts.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int rtc_unsubscribe_int();

/**
 * @brief Reads a register from the RTC.
 *
 * @param reg The register to read.
 * @param data Address of memory to store the register's data.
 * @return Return 0 upon success, non-zero otherwise.
 */
int rtc_read_register(uint8_t reg, uint8_t *data);

/**
 * @brief Writes data to a register of the RTC.
 *
 * @param reg The register to write to.
 * @param data The data to write.
 * @return Return 0 upon success, non-zero otherwise.
 */
int rtc_write_register(uint8_t reg, uint8_t data);

/**
 * @brief Starts the RTC.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int rtc_startup();

/**
 * @brief Stops the RTC.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int rtc_startdown();

/**
 * @brief Converts the BCD representation of data to binary.
 *
 * @param data Address of memory containing the BCD data.
 * @return Return 0 upon success, non-zero otherwise.
 */
int rtc_convert_bcd(uint8_t *data);

/**
 * @brief Updates the date using RTC data.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int rtc_update_date();

/**
 * @brief RTC interrupt handler.
 */
void rtc_int_handler();

/**
 * @struct Date
 * @brief Represents the current date and time.
 */
typedef struct Date {
    uint8_t seconds; ///< Seconds (0-59)
    uint8_t minutes; ///< Minutes (0-59)
    uint8_t hours;   ///< Hours (0-23)
    uint8_t day;     ///< Day of the month (1-31)
    uint8_t month;   ///< Month (1-12)
    uint8_t year;    ///< Year (0-99)
} Date_t;

#endif
