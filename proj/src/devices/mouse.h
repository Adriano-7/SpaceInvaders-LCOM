#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "macros.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

/**
 * @brief Construct a new int object
 * 
 */
int (mouse_get_status(uint8_t *st));

void(mouse_ih)();

/**
 * @brief  Mouse parse output.
 * 
 * @return true 
 * @return false 
 */
bool mouse_parse_output();

/**
 * @brief Complement of 2.
 * 
 * @param number 
 * @param msb 
 * @return uint16_t 
 */
uint16_t twoComplement(uint8_t* number, uint8_t msb);

void mouse_build_packet();

/**
 * @brief Writes KBC command.
 * 
 * @param port 
 * @param cmd 
 * @return int 
 */
int write_KBC_command(uint8_t port, uint8_t cmd);

/**
 * @brief Writes mouse cmd.
 * 
 * @param cmd 
 * @return int 
 */
int write_mouse_cmd(uint8_t cmd);

/**
 * @brief Disables data report.
 * 
 * @return int 
 */
int disable_data_report();

/**
 * @brief Enables data report.
 * 
 * @return int 
 */
int enable_data_report();

