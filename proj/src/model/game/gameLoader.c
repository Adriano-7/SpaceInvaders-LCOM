#include "gameLoader.h"

extern vbe_mode_info_t mode_info;

Entities_t* loadGame(){
    Player_t* player = createPlayer();
    if(player == NULL){
        printf("Error creating player\n");
        return NULL;
    }

    Monster_t* monsters[55];
    GameObject_t* gameObjects[56];

    int i = 0;
    gameObjects[i] = player->gameObject;
    i++;

    while (i < 56) {
        int x = (i % 11) * 50;
        int y = (i / 11) * 50;
        Monster_t* monster = createMonster(OSVALDO, x, y);
        if(monster == NULL){
            printf("Error creating monster\n");
            return NULL;
        }

        monsters[i - 1] = monster;
        gameObjects[i] = monster->gameObject;
        i++;
    }

    Entities_t* entities = createEntities(player, monsters, gameObjects);

    return entities;
}

void freeGame(){;}
