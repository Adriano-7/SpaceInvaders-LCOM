#include "loadXpm.h"

void loadXpms(){
    for(int i = 0; i < 4; i++){
        game_xpm_map[i] = xpm_load(game_xpm_name[i], XPM_INDEXED, &game_xpm[i]);
    }

    for(int i = 0; i < 2; i++){
        menu_xpm_map[i] = xpm_load(menu_xpm_name[i], XPM_INDEXED, &menu_xpm[i]);
    }

    for(int i = 0; i < 26; i++){
        letters_xpm_map[i] = xpm_load(letters_xpm_name[i], XPM_INDEXED, &letters_xpm[i]);
    }
}

void cleanXpms(){
    for(int i = 0; i < 4; i++){
        free(game_xpm_map[i]);
    }

    for(int i = 0; i < 2; i++){
        free(menu_xpm_map[i]);
    }

    for(int i = 0; i < 26; i++){
        free(letters_xpm_map[i]);
    }
}

