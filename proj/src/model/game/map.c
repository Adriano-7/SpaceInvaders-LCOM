#include "map.h"

extern vbe_mode_info_t mode_info;

Map_t* createMap(Player_t* player, Monster_t* monsters[55], GameObject_t* gameObjects[56]){
    Map_t* map = malloc(sizeof(Map_t));
    map->player = player;

    for(int i = 0; i < 55; i++){
        map->monsters[i] = monsters[i];
    }
        
    for(int i = 0; i < 56; i++){
        map->gameObjects[i] = gameObjects[i];
    }
    
    return map;
}

Map_t* loadGame(){
    Player_t* player = createPlayer(30);
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
        
        int x = (i % 11) * 60;
        int y = (i / 11) * 50 + mode_info.YResolution / 8;
        if(i % 11 == 0) y -= 50;

        enum MonsterType type;
        if(i < 12){
            type = MIRO;
            x += 5;
        } 
        else if(i < 34) type = OSVALDO;
        else type = IVAN;

        Monster_t* monster = createMonster(type, x, y, 2, 4);
        if(monster == NULL){
            printf("Error creating monster\n");
            return NULL;
        }

        monsters[i - 1] = monster;
        gameObjects[i] = monster->gameObject;
        i++;
    }

    Map_t* map = createMap(player, monsters, gameObjects);

    return map;
}

void freeGame(){;}
