#pragma once

#include <lcom/lcf.h>
#include "../drawableObject.h"
#include "../direction.h"
#include "../constants.h"

/**
 * @brief Enumerates the types of the monsters.
 * 
 */
enum MonsterType {
  OSVALDO,
  IVAN,
  MIRO
};

/**
 * @struct Monster
 * @brief Struct that characterizes the monsters.
 * 
 */
typedef struct Monster {
  DrawableObject_t* drawableObject;
  enum MonsterType monsterType;
  int points;
  enum DirectionX direction;
  int speedX;
  int speedY;
  int cur_image;
} Monster_t;

/**
 * @brief Create a Monster object
 * 
 * @param monsterType 
 * @param x 
 * @param y 
 * @param speedX 
 * @param speedY 
 * @return Monster_t* 
 */
Monster_t* createMonster(enum MonsterType monsterType, int x, int y, int speedX, int speedY);

/**
 * @brief Destroys the monsters.
 * 
 * @param monster 
 */
void destroyMonster(Monster_t* monster);

/**
 * @brief Animates the monsters.
 * 
 * @param monsters 
 */
void animateMonsters(Monster_t* monsters[NUM_MONSTERS]);

/**
 * @brief Get the Monster Image object
 * 
 * @param monster 
 * @param cur_image 
 * @param img 
 * @param img_colors 
 */
void getMonsterImage(Monster_t* monster, int cur_image, xpm_image_t* img, uint8_t** img_colors);

/**
 * @brief Get the Monster Image Index object
 * 
 * @param monsterType 
 * @return int 
 */
int getMonsterImageIndex(enum MonsterType monsterType);

/**
 * @brief Changes the monsters direction.
 * 
 * @param monster 
 */
void changeMonsterDirection(Monster_t* monster);

