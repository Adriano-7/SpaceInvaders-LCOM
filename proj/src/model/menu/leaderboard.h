#pragma once

#include <lcom/lcf.h>
#include "../../xpm/loadXpm.h"
#include <stdio.h>
#include "../../devices/rtc.h"

typedef struct Score {
    Date_t date;
    int score;
} Score_t;

typedef struct Leaderboard {
    Score_t* scores[3];
} Leaderboard_t;


Leaderboard_t* createLeaderboard();
Score_t* createScore(int score);
int addScore(int score);
int drawLeaderboard();
