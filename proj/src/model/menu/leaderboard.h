#pragma once

#include <lcom/lcf.h>
#include "../../xpm/loadXpm.h"
#include <stdio.h>
#include "../../devices/rtc.h"


typedef struct Score {

    real_time_info time;
    int score;

} Score_t;


int drawLeaderboard();
int writeFile();
void drawText();
void leaderboardAdd(int score);
