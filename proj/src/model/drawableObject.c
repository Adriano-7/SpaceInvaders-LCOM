#include "drawableObject.h"

extern vbe_mode_info_t mode_info;

DrawableObject_t* createdrawableObject(int x, int y, xpm_image_t img, uint8_t* img_colors,bool isVisible) {
    DrawableObject_t* obj = (DrawableObject_t*) malloc(sizeof(DrawableObject_t));
    if (obj == NULL){
        printf("Error creating drawableObject\n");
        return NULL;
    }
    obj->old_x = x;
    obj->old_y = y;
    obj->x = x;
    obj->y = y;
    obj->isVisible = isVisible;
    obj->img = img;
    obj->img_colors = img_colors;

    return obj;
}

void drawdrawableObject(DrawableObject_t* obj) {
    video_draw_rectangle(obj->old_x, obj->old_y, obj->img.width, obj->img.height, 0);

    if (obj->isVisible) {
        video_draw_xpm(obj->img, obj->img_colors, obj->x, obj->y);
    }
}
