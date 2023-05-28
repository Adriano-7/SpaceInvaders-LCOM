/**
 * @file monster.h
 * @brief Functions for handling monsters on the game map.
 */

#include <lcom/lcf.h>
#include "model/game/monster.h"
#include "model/game/map.h"
#include "model/direction.h"
#include "../../../state.h"

/**
 * @brief Moves the monsters on the game map.
 *
 * This function moves the monsters on the game map based on their current position, speed, and direction.
 *
 * @param map Pointer to the game map.
 */
void moveMonsters(Map_t* map);

/**
 * @brief Moves the monsters along the Y-axis.
 *
 * This function moves the monsters along the Y-axis on the game map.
 *
 * @param monsters Array of Monster structures.
 */
void moveMonstersY(Monster_t* monsters[NUM_MONSTERS]);

/**
 * @brief Moves the monsters along the X-axis.
 *
 * This function moves the monsters along the X-axis on the game map.
 *
 * @param monsters Array of Monster structures.
 */
void moveMonstersX(Monster_t* monsters[NUM_MONSTERS]);

/**
 * @brief Checks for collision between monsters and the player.
 *
 * This function checks for collision between the monsters and the player on the game map.
 *
 * @param monsters Array of Monster structures.
 * @param player Pointer to the player.
 * @return true if collision is detected, false otherwise.
 */
bool monstersCollidePlayer(Monster_t* monsters[NUM_MONSTERS], Player_t* player);

/**
 * @brief Checks for collision between monsters and walls.
 *
 * This function checks for collision between the monsters and walls on the game map.
 *
 * @param monsters Array of Monster structures.
 * @return true if collision is detected, false otherwise.
 */
bool monstersCollideWalls(Monster_t* monsters[NUM_MONSTERS]);

/**
 * @brief Detects collision between two drawable objects.
 *
 * This function checks for collision between two drawable objects on the game map.
 *
 * @param obj1 Pointer to the first drawable object.
 * @param obj2 Pointer to the second drawable object.
 * @return true if a collision is detected, false otherwise.
 */
bool detectCollision(DrawableObject_t* obj1, DrawableObject_t* obj2);
