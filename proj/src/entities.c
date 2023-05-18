#include "entities.h"

Entities_t* createEntities(Player_t* player, Monster_t* monsters[55], GameObject_t* gameObjects[56]){
    Entities_t* entities = malloc(sizeof(Entities_t));
    entities->player = player;

    for(int i = 0; i < 55; i++){
        entities->monsters[i] = monsters[i];
    }
        
    for(int i = 0; i < 56; i++){
        entities->gameObjects[i] = gameObjects[i];
    }
    
    return entities;
}


