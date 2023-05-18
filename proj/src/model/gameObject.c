#include "gameObject.h"
#include <lcom/lcf.h>

GameObject* createGameObject(int x, int y, int speed, xpm_image_t img, uint8_t* img_colors,bool isAlive) {
    GameObject* obj = (GameObject*) malloc(sizeof(GameObject));
    if (obj == NULL) {
        printf("Error creating GameObject\n");
        return NULL;
    }

    obj->x = x;
    obj->y = y;
    obj->speed = speed;
    obj->img = img;
    obj->img_colors = img_colors;
    obj->isAlive = isAlive;
    return obj;
}

void drawGameObject(GameObject* obj) {
    if (obj->isAlive) {
        draw_xpm(obj->img,obj->img_colors, obj->x, obj->y);
    }
}

