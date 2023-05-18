#include "menu.h"

Menu* createMenu() {
    char* options[] = {"Start", "LeaderBoard", "Exit"};
    int num_options = 3;
    int current_option = 0;

    Menu* menu = (Menu*) malloc(sizeof(Menu));
    menu->options = (char**) malloc(num_options * sizeof(char*));
    for (int i = 0; i < num_options; i++) {
        menu->options[i] = (char*) malloc(strlen(options[i]) + 1);
        strcpy(menu->options[i], options[i]);
    }
    menu->num_options = num_options;
    menu->current_option = current_option;

    return menu;
}

void next_Op(Menu* menu) {
    menu->current_option = (menu->current_option + 1) % menu->num_options;
}

void prev_Op(Menu* menu) {
    menu->current_option = (menu->current_option - 1 + menu->num_options) % menu->num_options;
}

const char* getCurrentOption(Menu* menu) {
    return menu->options[menu->current_option];
}

const char** getOptions(Menu* menu) {
    return (const char**) menu->options;
}
