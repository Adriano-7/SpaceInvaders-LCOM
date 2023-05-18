#include "entities.h"

Entities_t* createEntities(Player_t* player, Monster_t* monsters, GameObject_t* gameObjects[2]){
    Entities_t* entities = malloc(sizeof(Entities_t));
    entities->player = player;
    entities->monsters = monsters;
    for(int i = 0; i < 2; i++){
        entities->gameObjects[i] = gameObjects[i];
    }
    return entities;
}


