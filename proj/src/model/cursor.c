#include "cursor.h"

extern vbe_mode_info_t mode_info;

extern xpm_image_t symbol_xpm[4];
extern uint8_t* symbol_xpm_map[4];

Cursor_t* createCursor(){
    Cursor_t* cursor = (Cursor_t*)malloc(sizeof(Cursor_t));

    xpm_image_t img = symbol_xpm[1];
    uint8_t* img_colors = symbol_xpm_map[1];

    int x = (mode_info.XResolution - img.width)/2;
    int y = (mode_info.YResolution - img.height)/2;

    cursor->drawableObject = createdrawableObject(x, y, img, img_colors, true);
    cursor->drawableObject->x = x;
    cursor->drawableObject->y = y;
    cursor->lbPressed = false;

    return cursor;
}

void updateCursor(Cursor_t* cursor){
    cursor->drawableObject->old_x = cursor->drawableObject->x;
    cursor->drawableObject->old_y = cursor->drawableObject->y;
    
    video_draw_rectangle(cursor->drawableObject->x, cursor->drawableObject->y, cursor->drawableObject->img.width, cursor->drawableObject->img.height, 0);

    if(pkt.x_ov || pkt.y_ov){
        return;
    }

    cursor->drawableObject->x += pkt.delta_x;
    cursor->drawableObject->y -= pkt.delta_y;

    if(pkt.lb){
        cursor->lbPressed = true;
    }
    else{
        cursor->lbPressed = false;
    }

    if(cursor->drawableObject->x < 40){
        cursor->drawableObject->x = 40;
    }
    else if(cursor->drawableObject->x + cursor->drawableObject->img.width >= mode_info.XResolution - 40){
        cursor->drawableObject->x = mode_info.XResolution - cursor->drawableObject->img.width - 40;
    }

    if(cursor->drawableObject->y - cursor->drawableObject->img.height < 40){
        cursor->drawableObject->y = 40;
    }
    else if(cursor->drawableObject->y + cursor->drawableObject->img.height >= mode_info.YResolution - 40){
        cursor->drawableObject->y = mode_info.YResolution - cursor->drawableObject->img.height - 40;
    }
}

void destroyCursor(Cursor_t* cursor){
    free(cursor->drawableObject);
    free(cursor);
}

