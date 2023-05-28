#pragma once

#include <lcom/lcf.h>
#include "../../xpm/loadXpm.h"
#include <stdio.h>
#include "../../devices/rtc.h"

/**
 * @struct Score
 * @brief Gets data for Score.
 * 
 */
typedef struct Score {
    Date_t date;
    int score;
} Score_t;

/**
 * @struct Leaderbord
 * @brief Responsible for getting a leaderbord from the score.
 * 
 */
typedef struct Leaderboard {
    Score_t* scores[3];
} Leaderboard_t;

/**
 * @brief Create a Leaderboard object
 * 
 * @return Leaderboard_t* 
 */
Leaderboard_t* createLeaderboard();

/**
 * @brief Create a Score object
 * 
 * @param score 
 * @return Score_t* 
 */
Score_t* createScore(int score);

/**
 * @brief Adds the score.
 * 
 * @param score 
 * @return int 
 */
int addScore(int score);

/**
 * @brief Draws the leaderboard.
 * 
 * @return int 
 */
int drawLeaderboard();

/**
 * @brief Destroys the leaderboard.
 * 
 */
void destroyLeaderboard();
