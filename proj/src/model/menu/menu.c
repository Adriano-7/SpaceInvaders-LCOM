#include "menu.h"
#include "../../xpm/loadXpm.h"

extern vbe_mode_info_t mode_info;

Menu_t* createMenu(Option_t* options[NUM_OPTIONS], DrawableObject_t* drawableObjects[NUM_OPTIONS+1]) {
    Menu_t* menu = (Menu_t*) malloc(sizeof(Menu_t));

    for(int i=0; i<NUM_OPTIONS; i++){
        menu->options[i] = options[i];
    }

    for(int i=0; i<NUM_OPTIONS+1; i++){
        menu->drawableObjects[i] = drawableObjects[i];
    }

    return menu;
}

Menu_t* loadMenu(){
    Option_t* options[NUM_OPTIONS];
    DrawableObject_t* drawableObjects[NUM_OPTIONS+1];

    enum State state[NUM_OPTIONS] = {GAME, LEADERBOARD, EXIT};

    for(int i=0; i<NUM_OPTIONS + 1; i++){
        xpm_image_t img = menu_xpm[i];
        uint8_t* img_colors = menu_xpm_map[i];

        int x = (mode_info.XResolution - img.width)/2;
        int y = (mode_info.YResolution/8)*(i+1);

        i!=0 ? y+=140 : y;

        drawableObjects[i] = createdrawableObject(x, y, img, img_colors, true);

        if(i!=0){
            options[i-1] = createOption(state[i-1], drawableObjects[i]);
        }
    }

    return createMenu(options, drawableObjects);
}

void drawMenu(Menu_t* menu) {
    for(int i=0; i<4; i++){
        drawdrawableObject(menu->drawableObjects[i]);
    }
}

void destroyMenu(Menu_t* menu) {
    for(int i=0; i<NUM_OPTIONS; i++){
        destroyOption(menu->options[i]);
    }
    free(menu);
}

