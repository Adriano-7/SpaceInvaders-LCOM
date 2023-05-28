#pragma once

#include <lcom/lcf.h>
#include "../../xpm/loadXpm.h"
#include <stdio.h>
#include "../../devices/rtc.h"

typedef struct Score {
    Date_t date;
    int score;
} Score_t;

Score_t* createScore (int score, Date_t date);
int drawLeaderboard();
int writeFile();
void drawText();
void leaderboardAdd(int score);
