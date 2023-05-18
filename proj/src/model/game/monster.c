
#include "model/game/monster.h"
extern vbe_mode_info_t mode_info;

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
    monster->gameObject = createGameObject(x, y, 30, game_xpm[i] ,game_xpm_map[i],true);
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

void moveMonster(Monster_t* monster){
    if(monster == NULL) {
        printf("Error: monster is NULL in moveMonster\n");
        exit(EXIT_FAILURE);
    }

    monster->gameObject->old_x = monster->gameObject->x;
    monster->gameObject->old_y = monster->gameObject->y;

    bool canMoveRight = false;
    if( monster->gameObject->x + monster->gameObject->speed + monster->gameObject->img.width < mode_info.XResolution> 0){
        canMoveRight = true;
        }
    else{
        canMoveRight = false;
    }
    bool canMoveLeft = false;
    if(monster->gameObject->x - monster->gameObject->speed >= 0){
        canMoveLeft = true;
    }else{
        canMoveLeft = false;
    }

    switch(monster->direction){
        case RIGHT:
            if(canMoveRight){
                monster->gameObject->x += monster->gameObject->speed;
            }
            else{
                monster->gameObject->y += monster->gameObject->speed;
                monster->direction = LEFT;
            }
            break;
        case LEFT:
            if(canMoveLeft){
                monster->gameObject->x -= monster->gameObject->speed;
            }
            else{
                monster->gameObject->y += monster->gameObject->speed;
                monster->direction = RIGHT;
            }
            break;
        default:
            break;
    }
}

