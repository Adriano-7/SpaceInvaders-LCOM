#include <lcom/lcf.h>
#include "model/game/player.h"
#include "model/game/map.h"
#include "model/direction.h"

extern vbe_mode_info_t mode_info;

/**
 * @brief Moves the player on the game map.
 *
 * This function is responsible for moving the player on the game map based on the specified direction.
 * It takes a pointer to the player and the desired X-axis direction as input and updates the player's position
 * on the map accordingly.
 *
 * @param player Pointer to the player.
 * @param direction The X-axis direction in which the player should move.
 */
void movePlayer(Player_t* player, enum DirectionX direction);
