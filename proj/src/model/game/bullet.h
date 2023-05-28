/**
 * @file bullet.h
 * @brief Definition of the Bullet struct and related functions for bullet management.
 */

#ifndef BULLET_H
#define BULLET_H

#include <lcom/lcf.h>
#include "model/direction.h"
#include "../drawableObject.h"
#include "../../xpm/loadXpm.h"
#include "bulletType.h"

/**
 * @struct Bullet
 * @brief Structure representing a bullet in the game.
 */
typedef struct Bullet {
    DrawableObject_t* drawableObject; /**< Pointer to the bullet's drawable object. */
    enum BulletType type;             /**< Type of the bullet. */
    enum DirectionY direction;        /**< Direction of the bullet. */
    int speedY;                       /**< Vertical speed of the bullet. */
} Bullet_t;

/**
 * @brief Creates a bullet.
 * @param x Initial x-coordinate of the bullet.
 * @param y Initial y-coordinate of the bullet.
 * @param speedX Horizontal speed of the bullet.
 * @param direction Vertical direction of the bullet.
 * @param type Type of the bullet.
 * @return Pointer to the created Bullet_t object.
 */
Bullet_t* createBullet(int x, int y, int speedX, enum DirectionY direction, enum BulletType type);

/**
 * @brief Fires a bullet from a shooter.
 * @param bullet Pointer to the bullet to be fired.
 * @param shooter Pointer to the shooter's drawable object.
 * @param direction Vertical direction in which the bullet is fired.
 */
void fireBullet(Bullet_t* bullet, DrawableObject_t* shooter, enum DirectionY direction);

/**
 * @brief Destroys a bullet.
 * @param bullet Pointer to the bullet to be destroyed.
 */
void destroyBullet(Bullet_t* bullet);

#endif
