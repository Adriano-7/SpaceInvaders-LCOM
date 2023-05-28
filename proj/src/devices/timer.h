/**
 * @file timer.h
 * @brief Functions and constants for handling timers.
 */

#ifndef _LCOM_TIMER_H_
#define _LCOM_TIMER_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "macros.h"

/**
 * @brief Sets the frequency of a timer.
 *
 * @param timer The timer to set the frequency of.
 * @param freq The desired frequency.
 * @return Return 0 upon success, non-zero otherwise.
 */
int timer_set_frequency(uint8_t timer, uint32_t freq);

/**
 * @brief Subscribes to timer interrupts.
 *
 * @param bit_no Address of memory to store the hook_id bit number.
 * @return Return 0 upon success, non-zero otherwise.
 */
int timer_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes from timer interrupts.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int timer_unsubscribe_int();

/**
 * @brief Timer interrupt handler.
 */
void timer_int_handler();

/**
 * @brief Gets the configuration of a timer.
 *
 * @param timer The timer to get the configuration of.
 * @param st Address of memory to store the timer's configuration.
 * @return Return 0 upon success, non-zero otherwise.
 */
int timer_get_conf(uint8_t timer, uint8_t *st);

/**
 * @brief Displays the configuration of a timer.
 *
 * @param timer The timer to display the configuration of.
 * @param st The timer's configuration.
 * @param field The field of the configuration to display.
 * @return Return 0 upon success, non-zero otherwise.
 */
int timer_display_conf(uint8_t timer, uint8_t st, enum timer_status_field field);

#endif
