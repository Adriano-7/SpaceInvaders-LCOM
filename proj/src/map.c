#include "map.h"

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


