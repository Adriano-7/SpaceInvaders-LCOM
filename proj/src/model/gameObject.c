#include "gameObject.h"
#include <lcom/lcf.h>

extern vbe_mode_info_t mode_info;

GameObject_t* createGameObject(int x, int y, int speedX, int speedY, xpm_image_t img[2], uint8_t* img_colors[2],bool isAlive) {
    GameObject_t* obj = (GameObject_t*) malloc(sizeof(GameObject_t));
    if (obj == NULL) {
        printf("Error creating GameObject\n");
        return NULL;
    }
    obj->old_x = x;
    obj->old_y = y;
    obj->x = x;
    obj->y = y;
    obj->speedX = speedX;
    obj->speedY = speedY;
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

void drawGameObject(GameObject_t* obj) {
    vg_draw_rectangle(obj->old_x, obj->old_y, obj->img[obj->cur_image].width, obj->img[obj->cur_image].height, 0);

    if (obj->isAlive) {
        draw_xpm(obj->img[obj->cur_image],obj->img_colors[obj->cur_image], obj->x, obj->y);
    }
}
