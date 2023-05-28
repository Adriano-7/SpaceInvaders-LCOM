#include "leaderboard.h"

extern Date_t date;   
extern vbe_mode_info_t mode_info;

extern Leaderboard_t* leaderboard;

Leaderboard_t* createLeaderboard(){
    Leaderboard_t* new_leaderboard = malloc(sizeof(struct Leaderboard));

    new_leaderboard->scores[0] = createScore(0);
    new_leaderboard->scores[1] = createScore(0);
    new_leaderboard->scores[2] = createScore(0);

    return new_leaderboard;
}

Score_t* createScore(int score){
    Score_t* new_score = malloc(sizeof(struct Score));

    new_score->date = date;
    new_score->score = score;

    return new_score;
}

int addScore(int scorePts){
    int position = -1;

    Score_t* score = createScore(scorePts);

    for (int i = 0; i < 3; i++) {
        if (leaderboard->scores[i] == NULL || score->score > leaderboard->scores[i]->score) {
            position = i;
            break;
        }
    }

    if (position != -1) {
        for (int i = 2; i > position; i--) {
            leaderboard->scores[i] = leaderboard->scores[i - 1];
        }
        leaderboard->scores[position] = score;
    }

    return 0;
}

int drawLeaderboard(){
    video_draw_xpm(menu_xpm[4], menu_xpm_map[4], (mode_info.XResolution - menu_xpm[4].width)/2, (mode_info.YResolution/8));

    for(int i=0; i<3; i++){
        if(leaderboard->scores[i] != NULL){
            char score[20];
            sprintf(score, "%d", leaderboard->scores[i]->score);

            char date[20];
            sprintf(date, "%d/%d/%d %02d:%02d:%02d", leaderboard->scores[i]->date.day, leaderboard->scores[i]->date.month, leaderboard->scores[i]->date.year, leaderboard->scores[i]->date.hours, leaderboard->scores[i]->date.minutes, leaderboard->scores[i]->date.seconds);
            char* text = malloc(sizeof(char) * (strlen(score) + strlen(date) + 2));
            strcpy(text, score);
            strcat(text, " ");
            strcat(text, date);

            int textWidth = strlen(text) * 26;

            drawString(text, (mode_info.XResolution - textWidth) / 2, (mode_info.YResolution/8)*(i+1)+140);
        }
    }

    return 0;
}

void destroyLeaderboard(){
    for(int i=0; i<3; i++){
        if(leaderboard->scores[i] != NULL){
            free(leaderboard->scores[i]);
        }
    }

    free(leaderboard);
}

