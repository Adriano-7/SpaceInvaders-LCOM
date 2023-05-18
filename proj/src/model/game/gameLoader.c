#include "gameLoader.h"

extern vbe_mode_info_t mode_info;

Entities_t* loadGame(){
    Player_t* player = createPlayer();
    Monster_t* monster = createMonster(OSVALDO, 100, 100);
    GameObject_t* gameObjects[2] = {player->gameObject, monster->gameObject};

    Entities_t* entities = createEntities(player, monster, gameObjects);

    /*int i = 0;
    gameObjects[i] = player->gameObject;
    i++;

    while (i < 56) {
        int x = (i % 11) * 50;
        int y = (i / 11) * 50;
        Monster* monster = createMonster(OSVALDO, x, y);
        if(monster == NULL){
            printf("Error creating monster\n");
            return NULL;
        }

        monsters[i - 1] = monster;
        gameObjects[i] = monster->gameObject;
        i++;
    }
    */
    
    return entities;
}

void freeGame(){;}
