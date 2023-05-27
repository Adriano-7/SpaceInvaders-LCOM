#include <lcom/lcf.h>
#include "model/game/monster.h"
#include "model/game/map.h"
#include "model/direction.h"
#include "../../../state.h"

extern vbe_mode_info_t mode_info;

/**
 * @brief Moves the monsters on the game map.
 *
 * This function is responsible for moving the monsters on the game map based on their current position,
 * speed, and direction. It takes a pointer to the game map as input and updates the position of all the monsters
 * on the map.
 *
 * @param map Pointer to the game map.
 */
void moveMonsters(Map_t* map);

/**
 * @brief Moves the monsters along the Y-axis.
 *
 * This function is a helper function used by the moveMonsters() function to move the monsters along the Y-axis.
 * It takes an array of Monster structures as input and updates the Y position of each monster accordingly.
 *
 * @param monsters Array of Monster structures.
 */
void moveMonstersY(Monster_t* monsters[NUM_MONSTERS]);

/**
 * @brief Moves the monsters along the X-axis.
 *
 * This function is a helper function used by the moveMonsters() function to move the monsters along the X-axis.
 * It takes an array of Monster structures as input and updates the X position of each monster accordingly.
 *
 * @param monsters Array of Monster structures.
 */
void moveMonstersX(Monster_t* monsters[NUM_MONSTERS]);

/**
 * @brief Checks for collision between monsters and the player.
 *
 * This function checks for collision between the monsters and the player on the game map. It takes an array of Monster
 * structures and a pointer to the player as input. If a collision is detected, it returns true; otherwise, it returns false.
 *
 * @param monsters Array of Monster structures.
 * @param player Pointer to the player.
 * @return true if collision is detected, false otherwise.
 */
bool monstersCollidePlayer(Monster_t* monsters[NUM_MONSTERS], Player_t* player);

/**
 * @brief Checks for collision between monsters and walls.
 *
 * This function checks for collision between the monsters and walls on the game map. It takes an array of Monster
 * structures as input. If a collision is detected, it returns true; otherwise, it returns false.
 *
 * @param monsters Array of Monster structures.
 * @return true if collision is detected, false otherwise.
 */
bool monstersCollideWalls(Monster_t* monsters[NUM_MONSTERS]);

/**
 * @brief Detects collision between two drawable objects.
 *
 * This function checks for collision between two drawable objects on the game map. It takes two pointers to
 * DrawableObject structures as input and returns true if a collision is detected, and false otherwise.
 *
 * @param obj1 Pointer to the first drawable object.
 * @param obj2 Pointer to the second drawable object.
 * @return true if a collision is detected, false otherwise.
 */
bool detectCollision(DrawableObject_t* obj1, DrawableObject_t* obj2);
