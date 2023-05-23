#pragma once
#include <lcom/lcf.h>
#include "../devices/graphics.h"

typedef struct drawableObject {
    int x;
    int y;
    int old_x;
    int old_y;
    xpm_image_t img[2];
    uint8_t* img_colors[2];
    int cur_image;
    bool isVisible;
} drawableObject_t;

drawableObject_t* createdrawableObject(int x, int y, xpm_image_t img[2], uint8_t* img_colors[2],bool isVisible);
void drawdrawableObject(drawableObject_t* obj);
//void erasedrawableObject(drawableObject_t* obj);
