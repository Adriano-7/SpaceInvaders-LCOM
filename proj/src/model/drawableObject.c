#include "drawableObject.h"

extern vbe_mode_info_t mode_info;

drawableObject_t* createdrawableObject(int x, int y, xpm_image_t img[2], uint8_t* img_colors[2],bool isAlive) {
    drawableObject_t* obj = (drawableObject_t*) malloc(sizeof(drawableObject_t));
    if (obj == NULL) {
        printf("Error creating drawableObject\n");
        return NULL;
    }
    obj->old_x = x;
    obj->old_y = y;
    obj->x = x;
    obj->y = y;
    obj->isAlive = isAlive;
    obj->cur_image = 0;

    for (int i = 0; i < 2; i++) {
        obj->img[i] = img[i];
    }
    for (int i = 0; i < 2; i++) {
        obj->img_colors[i] = img_colors[i];
    }
    return obj;
}

void drawdrawableObject(drawableObject_t* obj) {
    vg_draw_rectangle(obj->old_x, obj->old_y, obj->img[obj->cur_image].width, obj->img[obj->cur_image].height, 0);

    if (obj->isAlive) {
        draw_xpm(obj->img[obj->cur_image],obj->img_colors[obj->cur_image], obj->x, obj->y);
    }
}



