#include "menu.h"
#include "../../xpm/loadXpm.h"

extern vbe_mode_info_t mode_info;

Menu_t* createMenu(Option_t* options[MENU_NUM_OPTIONS], DrawableObject_t* drawableObjects[MENU_NUM_DRAWABLE_OBJECTS], Cursor_t* cursor) {
    Menu_t* menu = (Menu_t*) malloc(sizeof(Menu_t));

    for(int i=0; i<MENU_NUM_OPTIONS; i++){
        menu->options[i] = options[i];
    }

    menu->cursor = cursor;

    for(int i=0; i<MENU_NUM_DRAWABLE_OBJECTS; i++){
        menu->drawableObjects[i] = drawableObjects[i];
    }

    menu->firstTime = true;

    return menu;
}

Menu_t* loadMenu(){
    Option_t* options[MENU_NUM_OPTIONS];
    DrawableObject_t* drawableObjects[MENU_NUM_DRAWABLE_OBJECTS];
    Cursor_t*cursor = createCursor();

    enum State state[MENU_NUM_OPTIONS] = {GAME, LEADERBOARD, EXIT};

    for(int i=0; i<MENU_NUM_OPTIONS + 1; i++){
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

    drawableObjects[MENU_NUM_DRAWABLE_OBJECTS-1] = cursor->drawableObject;

    return createMenu(options, drawableObjects, cursor);
}

void drawMenu(Menu_t* menu) {
    if(menu->firstTime){erase_screen(); menu->firstTime = false;}
    
    for(int i=0; i<MENU_NUM_DRAWABLE_OBJECTS; i++){
        drawdrawableObject(menu->drawableObjects[i]);
    }
}

void destroyMenu(Menu_t* menu) {
    for(int i=0; i<MENU_NUM_OPTIONS; i++){
        destroyOption(menu->options[i]);
    }
    free(menu);
}

