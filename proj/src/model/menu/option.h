/**
 * @file option.h
 * @brief Definition of the Option struct and related functions.
 */

#pragma once

#include <lcom/lcf.h>
#include "../drawableObject.h"
#include "../../state.h"

/**
 * @struct Option
 * @brief Structure representing a menu option.
 */
typedef struct Option {
    DrawableObject_t* drawableObject;  /**< Pointer to the DrawableObject associated with the option. */
    enum State state;                  /**< State associated with the option. */
} Option_t;

/**
 * @brief Creates a new Option object.
 * @param state State associated with the option.
 * @param drawableObject Pointer to the DrawableObject associated with the option.
 * @return Pointer to the created Option object.
 */
Option_t* createOption(enum State state, DrawableObject_t* drawableObject);

/**
 * @brief Destroys an Option object and frees the associated memory.
 * @param option Pointer to the Option object to be destroyed.
 */
void destroyOption(Option_t* option);
