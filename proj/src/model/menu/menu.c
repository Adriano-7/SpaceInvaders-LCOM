#include "menu.h"
#include "../../xpm/loadXpm.h"

Menu_t* createMenu() {
    Menu_t* menu = (Menu_t*) malloc(sizeof(Menu_t));



    for(int i=0; i<4; i++){

        xpm_image_t img[4];
        uint8_t* img_colors[4];

        img[0] = menu_xpm[i];
        img_colors[0] = menu_xpm_map[i];

        img[1] = menu_xpm[i];
        img_colors[1] = menu_xpm_map[i];

        img[2] = menu_xpm[i];
        img_colors[2] = menu_xpm_map[i];

        img[3] = menu_xpm[i];
        img_colors[3] = menu_xpm_map[i];


        //GameObject_t* createGameObject(int x, int y, int speedX, int speedY, xpm_image_t img[2], uint8_t* img_colors[2],bool isAlive) {
        GameObject_t* gameObject;

        if(i == 0){
            gameObject = createGameObject(175, 90, 0, 0, img, img_colors, true);
        }
        else if (i == 1) {
            gameObject = createGameObject(401, 349, 0, 0, img, img_colors, true);
        }
        else if (i == 2){
            gameObject = createGameObject(383, 437, 0, 0, img, img_colors, true);
        }
        else{
            gameObject = createGameObject(396, 525, 0, 0, img, img_colors, true);
        }

        if(gameObject == NULL){
            printf("Error creating gameObject\n");
            return NULL;
        }

        menu->gameObjects[i] = gameObject;
    }

    return menu;
}

void drawMenu(Menu_t* menu) {
    for(int i=0; i<4; i++){
        drawGameObject(menu->gameObjects[i]);
    }
}
