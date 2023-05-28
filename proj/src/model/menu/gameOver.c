#include "gameOver.h"

GameOver_t* createGameOver(Option_t* options[GAMEOVER_OPTIONS], DrawableObject_t* drawableObjects[GAMEOVER_NUM_DRAWABLE_OBJECTS], Cursor_t* cursor) {
    GameOver_t* gameover = (GameOver_t*) malloc(sizeof(GameOver_t));

    for(int i=0; i<GAMEOVER_OPTIONS; i++){
        gameover->options[i] = options[i];
    }

    gameover->cursor = cursor;

    for(int i=0; i<GAMEOVER_NUM_DRAWABLE_OBJECTS; i++){
        gameover->drawableObjects[i] = drawableObjects[i];
    }

    gameover->firstTime = true;

    return gameover;
}

GameOver_t* loadGameOver(){
    Option_t* options[GAMEOVER_OPTIONS];
    DrawableObject_t* drawableObjects[GAMEOVER_NUM_DRAWABLE_OBJECTS];
    Cursor_t*cursor = createCursor();

    enum State state[GAMEOVER_OPTIONS] = {GAME, MENU};

    for(int i=0; i<GAMEOVER_NUM_DRAWABLE_OBJECTS-1; i++){
        xpm_image_t img = gameover_xpm[i];
        uint8_t* img_colors = gameover_xpm_map[i];

        int x = (mode_info.XResolution - img.width)/2;
        int y = (mode_info.YResolution/8)*(i+1);

        i!=0 ? y+=140 : y;
        if(i == 1){
            drawableObjects[i] = createdrawableObject(x, 260, img, img_colors, true);
        }else{
            drawableObjects[i] = createdrawableObject(x, y, img, img_colors, true);
        }


        if(i==2 || i==3){
            options[i-2] = createOption(state[i-2], drawableObjects[i]);
        }
    }

    drawableObjects[GAMEOVER_NUM_DRAWABLE_OBJECTS-1] = cursor->drawableObject;

    return createGameOver(options, drawableObjects, cursor);
}


void drawGameOver(GameOver_t* gameover) {
    if(gameover->firstTime){erase_screen(); gameover->firstTime = false;}


    for(int i=0; i<GAMEOVER_NUM_DRAWABLE_OBJECTS; i++){
        drawdrawableObject(gameover->drawableObjects[i]);
    }

    drawNumber(map->lastScore, 480, 330, true);
}

void destroyGameOver(GameOver_t* gameover) {
    for(int i=0; i<GAMEOVER_OPTIONS; i++){
        destroyOption(gameover->options[i]);
    }
    free(gameover);
}
