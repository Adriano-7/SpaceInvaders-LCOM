#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    char** options;
    int num_options;
    int current_option;
} Menu;

Menu* createMenu();
void next_Op(Menu* menu);
void prev_Op(Menu* menu);
const char* getCurrentOption(Menu* menu);
const char** getOptions(Menu* menu);

#endif
