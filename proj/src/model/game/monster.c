
#include "model/game/monster.h"

extern xpm_image_t game_xpm[4];
extern uint8_t* game_xpm_map[4];

Monster_t* createMonster(enum MonsterType monsterType, int x, int y) {
    Monster_t* monster = malloc(sizeof(Monster_t));
    if (monster == NULL) {
        printf("Error: malloc failed in createMonster\n");
        exit(EXIT_FAILURE);
    }

    int i = getMonsterImageIndex(monsterType);
    monster->points = 10*i;
    monster->gameObject = createGameObject(x, y, 2, 4, game_xpm[i] ,game_xpm_map[i],true);
    monster->isAlive = true;
    monster->direction = RIGHT;

    return monster;
}

int getMonsterImageIndex(enum MonsterType monsterType){
    int i;
    switch(monsterType){
        case OSVALDO:
            i=1;
            break;
        case IVAN:
            i=2;
            break;
        case MIRO:
            i=3;
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

