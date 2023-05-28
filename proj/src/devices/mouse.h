/**
 * @file mouse.h
 * @brief Functions and constants for handling the mouse.
 */

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "macros.h"

/**
 * @brief Subscribes to mouse interrupts.
 *
 * @param bit_no Address of memory to store the hook_id bit number.
 * @return Return 0 upon success, non-zero otherwise.
 */
int mouse_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes from mouse interrupts.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int mouse_unsubscribe_int();

/**
 * @brief Gets the mouse status.
 *
 * @param st Address of memory to store the mouse status.
 * @return Return 0 upon success, non-zero otherwise.
 */
int mouse_get_status(uint8_t *st);

/**
 * @brief Mouse interrupt handler.
 */
void mouse_ih();

/**
 * @brief Parses the mouse output.
 *
 * @return True if parsing was successful, false otherwise.
 */
bool mouse_parse_output();

/**
 * @brief Calculates the two's complement of a number.
 *
 * @param number The number to calculate the complement for.
 * @param msb The most significant bit.
 * @return The calculated two's complement.
 */
uint16_t twoComplement(uint8_t* number, uint8_t msb);

/**
 * @brief Builds the mouse packet.
 */
void mouse_build_packet();

/**
 * @brief Writes a KBC command.
 *
 * @param port The KBC port.
 * @param cmd The command to write.
 * @return Return 0 upon success, non-zero otherwise.
 */
int write_KBC_command(uint8_t port, uint8_t cmd);

/**
 * @brief Writes a mouse command.
 *
 * @param cmd The mouse command to write.
 * @return Return 0 upon success, non-zero otherwise.
 */
int write_mouse_cmd(uint8_t cmd);

/**
 * @brief Disables data reporting from the mouse.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int disable_data_report();

/**
 * @brief Enables data reporting from the mouse.
 *
 * @return Return 0 upon success, non-zero otherwise.
 */
int enable_data_report();
