#pragma once
#include <lcom/lcf.h>
#include "../devices/graphics.h"

typedef struct DrawableObject {
    int x;
    int y;
    int old_x;
    int old_y;
    xpm_image_t img[2];
    uint8_t* img_colors[2];
    int cur_image;
    bool isAlive;
} DrawableObject_t;

DrawableObject_t* createdrawableObject(int x, int y, xpm_image_t img[2], uint8_t* img_colors[2],bool isAlive);
void drawdrawableObject(DrawableObject_t* obj);
//void erasedrawableObject(DrawableObject_t* obj);
