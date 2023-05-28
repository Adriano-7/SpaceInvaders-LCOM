#include "leaderboard.h"

extern Date_t date;   
extern vbe_mode_info_t mode_info;

Score_t* leaderboard[10];

Score_t* createScore (int score, Date_t date){
    Score_t* new_score = malloc(sizeof(struct Score));
    new_score->score = score;
    new_score->date = date;
    return new_score;
}

int count_digits(int number) {
    int digits = 0;
    int aux = number;

    if(number == 0) return 1;

    while (aux != 0) {
        aux /= 10;
        digits++;
    }

    return digits;
}

int drawLeaderboard(){
    video_draw_xpm(menu_xpm[4], menu_xpm_map[4], mode_info.XResolution/2 - menu_xpm[4].width/2, 70);
    
    for(int i = 0; i < 10; i++){
        if(leaderboard[i] != NULL){
            int x = 100;
            drawNumber(leaderboard[i]->score, x, 300 + i*60);
            //draw the date and time in front of it
            x += count_digits(leaderboard[i]->score) * 20 + 50;
            drawNumber(leaderboard[i]->date.day, x, 300 + i*60);
            x += count_digits(leaderboard[i]->date.day) * 20;
            drawString("/", x, 300 + i*60);
            x += 20;
            drawNumber(leaderboard[i]->date.month, x, 300 + i*60);
            x += count_digits(leaderboard[i]->date.month) * 30;
            drawString("/", x, 300 + i*60);
            x += 20;
            drawNumber(leaderboard[i]->date.year, x, 300 + i*60);

            x += count_digits(leaderboard[i]->date.year) * 20 + 50;

            drawNumber(leaderboard[i]->date.hours, x, 300 + i*60);
            x += count_digits(leaderboard[i]->date.hours) * 30;
            drawString(":", x, 300 + i*60);
            x += 20;
            drawNumber(leaderboard[i]->date.minutes, x, 300 + i*60);
            x += count_digits(leaderboard[i]->date.minutes) * 30;
            drawString(":", x, 300 + i*60);
            x += 20;
            drawNumber(leaderboard[i]->date.seconds, x, 300 + i*60);
        }
    }
    return 0;

}

void leaderboardAdd(int score){
    Score_t* newScore1 = createScore(1, date);
    Score_t* newScore2 = createScore(2, date);
    Score_t* newScore3 = createScore(3, date);

    leaderboard[0] = newScore1;
    leaderboard[1] = newScore2;
    leaderboard[2] = newScore3;

    Score_t* newScore = createScore(score, date);
    
    int position = -1;  // variable to track the position where the new score will be inserted

    for (int i = 0; i < 10; i++) {
        if (leaderboard[i] == NULL || newScore->score > leaderboard[i]->score) {
            position = i;
            break;
        }
    }

    if (position != -1) {
        // Shift the scores down to make room for the new score
        for (int i = 9; i > position; i--) {
            leaderboard[i] = leaderboard[i - 1];
        }

        // Insert the new score at the desired position
        leaderboard[position] = newScore;
    } else {
        // The new score does not qualify for the leaderboard
        printf("The new score is not high enough for the leaderboard.");
    }
        
        return;
}

int writeFile(){
 /*   FILE *file = fopen("../../leaderboard.txt", "w");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
    printf("Success\n");

    for(int i = 0; i < 10; i++){
        fprintf(file, "%d\n", leaderboard[i].score);
    }
    */
    return 0;
}

void drawText(){
    /*
    struct Score scores[10];

    FILE *file = fopen("../../leaderboard.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

   int i = 0;
    while (fscanf(file, "%d %s %s", &scores[i].score, scores[i].date, scores[i].time) == 3) {
        printf("Entered %d time\n",i);
        i++;
    }

    fclose(file);
    */
   return;
}
