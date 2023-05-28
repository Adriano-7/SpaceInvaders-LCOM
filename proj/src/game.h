#ifndef _LCOM_GAME_H_
#define _LCOM_GAME_H_

#include <lcom/lcf.h>
#include "state.h"

#include "model/game/map.h"
#include "xpm/loadXpm.h"

#include "model/menu/leaderboard.h"
#include "model/menu/gameOver.h"

#include "controllers/handleInterrupt.h"

#include "devices/keyboard.h"
#include "devices/timer.h"
#include "devices/video.h"
#include "devices/mouse.h"
#include "devices/rtc.h"

/**
 * @brief Main function for running the game loop.
 * @return Return 0 upon success and non-zero otherwise.
 *
 * This function is the entry point for running the game loop. It initializes the necessary components,
 * handles interrupts, and updates the game state based on user input and timers. It continues to run
 * until the game is exited or an error occurs.
 */
int (game_loop)();

#endif
