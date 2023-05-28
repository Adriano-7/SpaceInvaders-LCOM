#ifndef STATE_H
#define STATE_H

#include "devices/video.h"

enum State {MENU, LEADERBOARD, GAME, GAMEOVER, EXIT};

/**
 * @brief Pointer to the current state of the game.
 *
 * This variable holds the current state of the game as an enum State value.
 * It is accessible from other files as an external variable.
 */
extern enum State* state;

/**
 * @brief Changes the state of the game.
 * 
 * @param newState The new state to set for the game.
 *
 * This function is used to change the state of the game to a new state specified
 * by the newState parameter.
 */
void changeState(enum State newState);

#endif /* STATE_H */
