#pragma once
#include <lcom/lcf.h>
#include "../devices/video.h"

typedef struct DrawableObject {
    int x;
    int y;
    int old_x;
    int old_y;
    xpm_image_t img;
    uint8_t* img_colors;
    bool isVisible;
} DrawableObject_t;

DrawableObject_t* createdrawableObject(int x, int y, xpm_image_t img, uint8_t* img_colors, bool isVisible);
void drawdrawableObject(DrawableObject_t* obj);
