#include "model/menu/menu.h"
#include <stdio.h>

void drawMenu(Menu* menu) {
    const char** options = getOptions(menu);
    int num_options = menu->num_options;
    int current_option = menu->current_option;

    drawTitle();
    drawOptions(options, num_options, current_option);
}

void drawTitle() {}

void drawOptions(const char** options, int num_options, int current_option) {}