#include "gameObject.h"
#include <lcom/lcf.h>

extern vbe_mode_info_t mode_info;

GameObject_t* createGameObject(int x, int y, int speed, xpm_image_t img, uint8_t* img_colors,bool isAlive) {
    GameObject_t* obj = (GameObject_t*) malloc(sizeof(GameObject_t));
    if (obj == NULL) {
        printf("Error creating GameObject\n");
        return NULL;
    }
    obj->old_x = x;
    obj->old_y = y;
    obj->x = x;
    obj->y = y;
    obj->speed = speed;
    obj->img = img;
    obj->img_colors = img_colors;
    obj->isAlive = isAlive;
    return obj;
}

void drawGameObject(GameObject_t* obj) {
    vg_draw_rectangle(obj->old_x, obj->old_y, obj->img.width, obj->img.height, 0);

    if (obj->isAlive) {
        draw_xpm(obj->img,obj->img_colors, obj->x, obj->y);
    }
}

