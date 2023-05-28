#pragma once
#include <lcom/lcf.h>
#include "player.h"
#include "monster.h"
#include "bullet.h"
#include "../drawableObject.h"

#include "../constants.h"
#include "../../state.h"
#include "../menu/leaderboard.h"


extern vbe_mode_info_t mode_info;


/**
 * @struct Map
 * @brief Creates the map.
 */
typedef struct Map{
    Player_t* player; 
    Monster_t* monsters[NUM_MONSTERS]; 
    Bullet_t* bullets[NUM_BULLETS];
    DrawableObject_t* drawableObjects[GAME_NUM_DRAWABLE_OBJECTS];

    int lastScore;
    int visibleMonsters;
} Map_t;

/**
 * @brief Create a Map object
 * 
 * @param player 
 * @param monsters 
 * @param bullets 
 * @param drawableObjects 
 * @return Map_t* 
 */
Map_t* createMap(Player_t* player, Monster_t* monsters[NUM_MONSTERS], Bullet_t* bullets[NUM_BULLETS], DrawableObject_t* drawableObjects[GAME_NUM_DRAWABLE_OBJECTS]);

/**
 * @brief Loads the game
 * 
 * @return Map_t* 
 */
Map_t* loadGame();

/**
 * @brief Draws the map.
 * 
 * @param map 
 */
void drawMap(Map_t* map);

/**
 * @brief Draws the score.
 * 
 * @param score 
 */
void drawScore(int score);

/**
 * @brief Draws the live bar.
 * 
 * @param lives 
 */
void drawLiveBar(int lives);

/**
 * @brief Resets the map.
 * 
 * This function is responsible for resetting the map and all elements around it.
 * 
 * @param map 
 * @param decreaseLives 
 * @param resetScore 
 * @param resetLives 
 * @param resetMonsters 
 */
void resetMap(Map_t* map, bool decreaseLives, bool resetScore, bool resetLives, bool resetMonsters);

/**
 * @brief Destroys the map.
 * 
 * This function is responsible for destroying the map.
 * 
 * @param map 
 */
void destroyMap(Map_t* map);
