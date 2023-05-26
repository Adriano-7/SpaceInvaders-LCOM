#include "pauseMenu.h"
#include "../../xpm/loadXpm.h"

extern vbe_mode_info_t mode_info;

PauseMenu_t* createPauseMenu(Option_t* options[NUM_OPTIONS], DrawableObject_t* drawableObjects[NUM_OPTIONS+2], Cursor_t* cursor) {
    PauseMenu_t* pauseMenu = (PauseMenu_t*) malloc(sizeof(PauseMenu_t));

    for(int i=0; i<NUM_OPTIONS; i++){
        pauseMenu->options[i] = options[i];
    }

    pauseMenu->cursor = cursor;

    for(int i=0; i<NUM_OPTIONS+2; i++){
        pauseMenu->drawableObjects[i] = drawableObjects[i];
    }

    return pauseMenu;
}

PauseMenu_t* loadPauseMenu(){
    Option_t* options[NUM_OPTIONS];
    DrawableObject_t* drawableObjects[NUM_OPTIONS+2];
    Cursor_t* cursor = createCursor();

    enum State state[NUM_OPTIONS] = {RESUME, EXIT};

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

    drawableObjects[NUM_OPTIONS+1] = cursor->drawableObject;

    return createPauseMenu(options, drawableObjects, cursor);
}

void drawPauseMenu(PauseMenu_t* pauseMenu) {
    for(int i=0; i<NUM_OPTIONS+2; i++){
        drawdrawableObject(pauseMenu->drawableObjects[i]);
    }
}

void destroyPauseMenu(PauseMenu_t* pauseMenu) {
    for(int i=0; i<NUM_OPTIONS; i++){
        destroyOption(pauseMenu->options[i]);
    }
    free(pauseMenu);
}

void openPauseMenu() {
    PauseMenu_t* pauseMenu = loadPauseMenu();
    drawPauseMenu(pauseMenu);
}