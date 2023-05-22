
#include "model/game/monster.h"

extern xpm_image_t game_xpm[4];
extern uint8_t* game_xpm_map[4];

Monster_t* createMonster(enum MonsterType monsterType, int x, int y, int speedX, int speedY) {
    Monster_t* monster = malloc(sizeof(Monster_t));
    if (monster == NULL) {
        printf("Error: malloc failed in createMonster\n");
        exit(EXIT_FAILURE);
    }

    xpm_image_t img[2];
    uint8_t* img_colors[2];

    img[0] = game_xpm[getMonsterImageIndex(monsterType)];
    img_colors[0] = game_xpm_map[getMonsterImageIndex(monsterType)];

    img[1] = game_xpm[getMonsterImageIndex(monsterType) + 1];
    img_colors[1] = game_xpm_map[getMonsterImageIndex(monsterType) + 1];

    

    int i = getMonsterImageIndex(monsterType);
    monster->points = 10*i;
    monster->gameObject = createGameObject(x, y, img ,img_colors,true);
    monster->isAlive = true;
    monster->direction = RIGHT;
    monster->speedX = speedX;
    monster->speedY = speedY;

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

void destroyMonster(Monster_t* monster){
    free(monster->gameObject);
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

