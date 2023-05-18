#pragma once
#include <lcom/lcf.h>
#include "../devices/graphics.h"

typedef struct GameObject {
    int x;
    int y;
    int old_x;
    int old_y;
    int speed;
    xpm_image_t img;
    uint8_t* img_colors;
    bool isAlive;
} GameObject_t;

GameObject_t* createGameObject(int x, int y, int speed, xpm_image_t img, uint8_t* img_colors,bool isAlive);
void drawGameObject(GameObject_t* obj);
//void eraseGameObject(GameObject_t* obj);

