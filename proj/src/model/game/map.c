#include "map.h"

extern vbe_mode_info_t mode_info;

Map_t* createMap(Player_t* player, Monster_t* monsters[55], Bullet_t* bullet, DrawableObject_t* drawableObjects[57]){
    Map_t* map = malloc(sizeof(Map_t));
    map->player = player;

    for(int i = 0; i < 55; i++){
        map->monsters[i] = monsters[i];
    }
    
    map->bullet = bullet;

    for(int i = 0; i < 57; i++){
        map->drawableObjects[i] = drawableObjects[i];
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
    DrawableObject_t* drawableObjects[57];

    int i = 0;
    drawableObjects[i] = player->drawableObject;
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
        drawableObjects[i] = monster->drawableObject;
        i++;
    }

    Bullet_t* bullet = createBullet(0, 40, 4, UP);
    if(bullet == NULL){
        printf("Error creating bullet\n");
        return NULL;
    }
    drawableObjects[i] = bullet->drawableObject;

    Map_t* map = createMap(player, monsters, bullet, drawableObjects);

    return map;
}

void drawMap(Map_t* map){
    for(int i = 0; i < 57; i++){
        if(map->drawableObjects[i] != NULL && map->drawableObjects[i]->isVisible == true){
            drawdrawableObject(map->drawableObjects[i]);
        }
    }

    drawString("score:", mode_info.XResolution / 40, mode_info.YResolution / 40);
    drawScore(map->player->score);
    drawLiveBar(map->player->lives);
}

void drawScore(int score){
    vg_draw_rectangle(0, 0, mode_info.XResolution / 2, mode_info.YResolution / 30, 0);

    drawString("score:", mode_info.XResolution / 40, mode_info.YResolution / 40);
    drawNumber(score, mode_info.XResolution / 40 + 6 * 23, mode_info.YResolution / 40);
}

void drawLiveBar(int lives) {
  for (int i = 0; i < lives; i++) {
    draw_xpm(symbol_xpm[0], symbol_xpm_map[0], mode_info.XResolution - (i+1)*symbol_xpm[0].width - mode_info.XResolution / 40, mode_info.YResolution / 40);
  }
}

void destroyMap(Map_t* map){;
    destroyPlayer(map->player);
    for(int i = 0; i < 55; i++){
        destroyMonster(map->monsters[i]);
    }
    free(map);
}
