#include "model/game/monster.h"

extern xpm_image_t game_xpm[4];
extern uint8_t* game_xpm_map[4];

Monster_t* createMonster(enum MonsterType monsterType, int x, int y, int speedX, int speedY) {
    Monster_t* monster = malloc(sizeof(Monster_t));
    if (monster == NULL) {
        printf("Error: malloc failed in createMonster\n");
        exit(EXIT_FAILURE);
    }


    int i = getMonsterImageIndex(monsterType);

    xpm_image_t img = game_xpm[i];
    uint8_t* img_colors = game_xpm_map[i];
    monster->points = 10*i;
    monster->drawableObject = createdrawableObject(x, y, img ,img_colors,true);
    monster->direction = RIGHT;
    monster->speedX = speedX;
    monster->speedY = speedY;
    monster->monsterType = monsterType;

    return monster;
}

int getMonsterImageIndex(enum MonsterType monsterType){
    int i;
    switch(monsterType){
        case OSVALDO:
            i=1;
            break;
        case IVAN:
            i=3;
            break;
        case MIRO:
            i=5;
            break;
        default:
            break;
    }
    return i;
}

void animateMonsters(Monster_t* monsters[NUM_MONSTERS]){
    for(int i=0; i<NUM_MONSTERS; i++){
        xpm_image_t img;
        uint8_t* img_colors;
        getMonsterImage(monsters[i], monsters[i]->cur_image, &img, &img_colors);

        if(monsters[i]->cur_image == 0){
            monsters[i]->cur_image = 1;
        }
        else{
            monsters[i]->cur_image = 0;
        }

        monsters[i]->drawableObject->img = img;
        monsters[i]->drawableObject->img_colors = img_colors;
    }
}

void getMonsterImage(Monster_t* monster, int cur_image, xpm_image_t* img, uint8_t** img_colors){
    *img = game_xpm[getMonsterImageIndex(monster->monsterType) + cur_image];
    *img_colors = game_xpm_map[getMonsterImageIndex(monster->monsterType) + cur_image];
}


void destroyMonster(Monster_t* monster){
    free(monster->drawableObject);
    free(monster);
}

void changeMonsterDirection(Monster_t* monster){
    if(monster->direction == RIGHT){
        monster->direction = LEFT;
    }
    else{
        monster->direction = RIGHT;
    }
}

