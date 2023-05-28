/**
 * @file collision.h
 * @brief Functions for handling collisions on the game map.
 */

#include <lcom/lcf.h>
#include "model/game/bullet.h"
#include "model/game/map.h"
#include "model/direction.h"
#include "../../../model/menu/leaderboard.h"

/**
 * @brief Moves the bullets on the game map.
 *
 * This function moves the bullets on the game map based on their current position, speed, and direction.
 *
 * @param map Pointer to the game map.
 */
void moveBullets(Map_t* map);

/**
 * @brief Handles collision between a player and a bullet.
 *
 * This function checks for collision between a player and a bullet on the game map.
 *
 * @param map Pointer to the game map.
 * @param bullet Pointer to the bullet.
 */
void playerBulletCollision(Map_t* map, Bullet_t* bullet);

/**
 * @brief Handles collision between a monster and a bullet.
 *
 * This function checks for collision between a monster and a bullet on the game map.
 *
 * @param map Pointer to the game map.
 * @param bullet Pointer to the bullet.
 */
void monsterBulletCollision(Map_t* map, Bullet_t* bullet);

/**
 * @brief Detects collision between two drawable objects.
 *
 * This function checks for collision between two drawable objects on the game map.
 *
 * @param obj1 Pointer to the first drawable object.
 * @param obj2 Pointer to the second drawable object.
 * @return true if a collision is detected, false otherwise.
 */
bool detectObjectCollision(DrawableObject_t* obj1, DrawableObject_t* obj2);

/**
 * @brief Handles collision between a bullet and a wall.
 *
 * This function checks for collision between a bullet and a wall on the game map.
 *
 * @param bullet Pointer to the bullet.
 */
void wallCollision(Bullet_t* bullet);
