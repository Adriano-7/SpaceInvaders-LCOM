#pragma once
#include <lcom/lcf.h>
#include "../devices/graphics.h"

typedef struct {
    int x;
    int y;
    int speed;
    xpm_image_t img;
    uint8_t* img_colors;
    bool isAlive;
} GameObject;

GameObject* createGameObject(int x, int y, int speed, xpm_image_t img, uint8_t* img_colors,bool isAlive);
void drawGameObject(GameObject* obj);

