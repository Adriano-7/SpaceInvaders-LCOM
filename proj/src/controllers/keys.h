#pragma once
#include <lcom/lcf.h>
#include <stdint.h>

#include "../devices/macros.h"

/**
 * @brief Enumeration of keyboard keys.
 *
 * This enumeration defines the different keyboard keys that can be pressed.
 */
enum Keys {
    Make_Arrow_left,    /**< Left arrow key */
    Make_Arrow_right,   /**< Right arrow key */
    Make_Spacebar,      /**< Spacebar key */
    Make_Esc,           /**< Escape key */
    KEY_NONE,           /**< No key */
};

/**
 * @brief Gets the corresponding key from the keyboard input bytes.
 *
 * This function takes an array of two keyboard input bytes and returns the corresponding key.
 *
 * @param bytes Array containing the keyboard input bytes.
 * @return The corresponding key based on the input bytes.
 */
enum Keys get_key(uint8_t bytes[2]);
