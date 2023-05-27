#include "over.h"
#include "../../xpm/loadXpm.h"

Over_t* createOver(Option_t* options[OVER_OPTIONS], DrawableObject_t* drawableObjects[OVER_OPTIONS+2], Cursor_t* cursor) {
    Over_t* over = (Over_t*) malloc(sizeof(Over_t));

    for(int i=0; i<OVER_OPTIONS; i++){
        over->options[i] = options[i];
    }

    over->cursor = cursor;

    for(int i=0; i<OVER_OPTIONS+2; i++){
        over->drawableObjects[i] = drawableObjects[i];
    }

    return over;
}

Over_t* loadOver(){
    Option_t* options[OVER_OPTIONS];
    DrawableObject_t* drawableObjects[OVER_OPTIONS+2];
    Cursor_t*cursor = createCursor();

    enum State state[OVER_OPTIONS] = {GAME, MENU};

    for(int i=0; i<OVER_OPTIONS + 1; i++){
        xpm_image_t img = gameover_xpm[i];
        uint8_t* img_colors = gameover_xpm_map[i];

        int x = (mode_info.XResolution - img.width)/2;
        int y = (mode_info.YResolution/8)*(i+1);

        i!=0 ? y+=140 : y;

        drawableObjects[i] = createdrawableObject(x, y, img, img_colors, true);

        if(i!=0){
            options[i-1] = createOption(state[i-1], drawableObjects[i]);
        }
    }

    drawableObjects[OVER_OPTIONS+1] = cursor->drawableObject;

    return createOver(options, drawableObjects, cursor);
}


void drawOver(Over_t* over) {
    for(int i=0; i<OVER_OPTIONS+2; i++){
        drawdrawableObject(over->drawableObjects[i]);
    }
}

void destroyOver(Over_t* over) {
    for(int i=0; i<OVER_OPTIONS; i++){
        destroyOption(over->options[i]);
    }
    free(over);
}
