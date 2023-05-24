#include "menu.h"
#include "../../xpm/loadXpm.h"

extern vbe_mode_info_t mode_info;

Menu_t* createMenu() {
    Menu_t* menu = (Menu_t*) malloc(sizeof(Menu_t));

    for(int i=0; i<4; i++){
        xpm_image_t img = menu_xpm[i];
        uint8_t* img_colors = menu_xpm_map[i];

        int x = (mode_info.XResolution - img.width)/2;
        int y = (mode_info.YResolution/8)*(i+1);

        i!=0 ? y+=140 : y; //space between logo and options


        DrawableObject_t* drawableObject = createdrawableObject(x, y, img, img_colors, true);
        if(drawableObject == NULL){
            printf("Error creating drawableObject\n");
            return NULL;
        }

        menu->drawableObjects[i] = drawableObject;
    }

    return menu;
}

void drawMenu(Menu_t* menu) {
    for(int i=0; i<4; i++){
        drawdrawableObject(menu->drawableObjects[i]);
    }
}
