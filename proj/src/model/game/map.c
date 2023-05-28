#include "map.h"


Map_t* createMap(Player_t* player, Monster_t* monsters[NUM_MONSTERS], Bullet_t* bullets[NUM_BULLETS], DrawableObject_t* drawableObjects[GAME_NUM_DRAWABLE_OBJECTS]){
    Map_t* map = malloc(sizeof(Map_t));
    map->player = player;

    for(int i = 0; i < NUM_MONSTERS; i++){
        map->monsters[i] = monsters[i];
    }
    
    for(int i = 0; i < NUM_BULLETS; i++){
        map->bullets[i] = bullets[i];
    }

    for(int i = 0; i < GAME_NUM_DRAWABLE_OBJECTS; i++){
        map->drawableObjects[i] = drawableObjects[i];
    }
    
    map->lastScore = 0;
    map->visibleMonsters = NUM_MONSTERS;

    return map;
}

Map_t* loadGame(){
    Player_t* player = createPlayer(30);

    if(player == NULL){
        printf("Error creating player\n");
        return NULL;
    }

    Monster_t* monsters[NUM_MONSTERS];
    DrawableObject_t* drawableObjects[GAME_NUM_DRAWABLE_OBJECTS];
    Bullet_t* bullets[NUM_BULLETS];

    int i = 0;
    drawableObjects[i] = player->drawableObject;
    i++;

    while (i < NUM_MONSTERS+1) {
        int x = (i % 11) * 70;
        int y = (i / 11) * 50 + mode_info.YResolution / 8;
        if(i % 11 == 0) y -= 50;

        enum MonsterType type;
        if(i < 12){
            type = MIRO;
            x += 5;
        } 
        else if(i < 34) type = OSVALDO;
        else type = IVAN;

        Monster_t* monster = createMonster(type, x+150, y, 1, 20);
        if(monster == NULL){
            printf("Error creating monster\n");
            return NULL;
        }

        monsters[i - 1] = monster;
        drawableObjects[i] = monster->drawableObject;
        i++;
    }

    int j = 0;
    bullets[j] = createBullet(0, 0, 10, UP, PLAYER);
    drawableObjects[i] = bullets[j]->drawableObject;
    i++;
    j++;

    while(j < NUM_BULLETS){
        bullets[j] = createBullet(0, 0, 8, DOWN, MONSTER);
        drawableObjects[i] = bullets[j]->drawableObject;
        i++;
        j++;
    }

    Map_t* map = createMap(player, monsters, bullets, drawableObjects);

    return map;
}

void drawMap(Map_t* map){
    if(map->visibleMonsters == 0){
        resetMap(map, false, false, true, true);
    }

    for(int i = 0; i < GAME_NUM_DRAWABLE_OBJECTS; i++){
        if(map->drawableObjects[i] != NULL && map->drawableObjects[i]->isVisible == true){
            drawdrawableObject(map->drawableObjects[i]);
        }
    }

    drawString("score:", mode_info.XResolution / 40, mode_info.YResolution / 40);
    drawScore(map->player->score);
    drawLiveBar(map->player->lives);
}

void drawScore(int score){
    video_draw_rectangle(0, 0, mode_info.XResolution / 2, mode_info.YResolution / 30, 0);

    drawString("score:", mode_info.XResolution / 40, mode_info.YResolution / 40);
    drawNumber(score, mode_info.XResolution / 40 + 6 * 23, mode_info.YResolution / 40, false);
}

void drawLiveBar(int lives) {
  for (int i = 0; i < lives; i++) {
    video_draw_xpm(game_xpm[8], game_xpm_map[8], mode_info.XResolution - (i+1)*game_xpm[8].width - mode_info.XResolution / 40, mode_info.YResolution / 40);
  }
}

void resetMap(Map_t* map, bool decreaseLives, bool resetScore, bool resetLives, bool resetMonsters){
    map->player->drawableObject->x = (mode_info.XResolution/2)-(game_xpm[0].width/2);
    map->player->drawableObject->old_x = (mode_info.XResolution/2)-(game_xpm[0].width/2);
    map->player->drawableObject->y = mode_info.YResolution - game_xpm[0].height - 10;
    map->player->drawableObject->old_y = mode_info.YResolution - game_xpm[0].height - 10;
    
    if(decreaseLives){
        map->player->lives--;
        if(map->player->lives==0){
            addScore(map->player->score);
            map->lastScore = map->player->score;
            resetMap(map, false, true, true, true);
            changeState(GAMEOVER);
        }
    }
    if(resetScore){map->player->score = 0;}
    if(resetLives){map->player->lives = 3;}
    
    if(resetMonsters){
        map->visibleMonsters = NUM_MONSTERS;

        int i = 0;
        i++;

        while (i < NUM_MONSTERS+1) {
            int x = (i % 11) * 70;
            int y = (i / 11) * 50 + mode_info.YResolution / 8;
            if(i % 11 == 0) y -= 50;
    
            if(i < 12){
                x += 5;
            } 
    
            map->monsters[i - 1]->drawableObject->x = x+150;
            map->monsters[i - 1]->drawableObject->old_x = x+150;
            map->monsters[i - 1]->drawableObject->y = y;
            map->monsters[i - 1]->drawableObject->old_y = y;
            map->monsters[i - 1]->drawableObject->isVisible = true;
            map->monsters[i - 1]->direction = RIGHT;
    
            i++;
        }
    }

    for(int i = 0; i < NUM_BULLETS; i++){
        map->bullets[i]->drawableObject->isVisible = false;
        map->bullets[i]->drawableObject->x = 0;
        map->bullets[i]->drawableObject->old_x = 40;
        map->bullets[i]->drawableObject->y = 0;
        map->bullets[i]->drawableObject->old_y = 40;
    }
    
    erase_screen();
}

void destroyMap(Map_t* map){;
    destroyPlayer(map->player);
    for(int i = 0; i < NUM_MONSTERS; i++){
        destroyMonster(map->monsters[i]);
    }
    free(map);
}
