#pragma once
#include <lcom/lcf.h>
#include "../../devices/graphics.h"

typedef struct GameObject {
    int x;
    int y;
    int old_x;
    int old_y;
    xpm_image_t img[2];
    uint8_t* img_colors[2];
    int cur_image;
    bool isAlive;
} GameObject_t;

GameObject_t* createGameObject(int x, int y, xpm_image_t img[2], uint8_t* img_colors[2],bool isAlive);
void drawGameObject(GameObject_t* obj);
//void eraseGameObject(GameObject_t* obj);
