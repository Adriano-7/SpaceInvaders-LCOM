#include "loadXpm.h"

void loadXpms(){
    for(int i = 0; i < 5; i++){
        game_xpm_map[i] = xpm_load(game_xpm_name[i], XPM_INDEXED, &game_xpm[i]);
    }

    for(int i = 0; i < 2; i++){
        menu_xpm_map[i] = xpm_load(menu_xpm_name[i], XPM_INDEXED, &menu_xpm[i]);
    }
    for(int i = 0; i< 2; i++){
        symbol_xpm_map[i] = xpm_load(symbol_xpm_name[i], XPM_INDEXED, &symbol_xpm[i]);
    }

    for(int i = 0; i < 26; i++){
        letters_xpm_map[i] = xpm_load(letters_xpm_name[i], XPM_INDEXED, &letters_xpm[i]);
    }
    for (int i = 0; i < 10; i++){
        numbers_xpm_map[i] = xpm_load(numbers_xpm_name[i], XPM_INDEXED, &numbers_xpm[i]);
    }
}

void cleanXpms(){
    for(unsigned int i = 0; i < sizeof(game_xpm_map); i++){
        free(game_xpm_map[i]);
    }
    for (int i = 0; i < 10; i++){
        free(numbers_xpm_map[i]);
    }

    for(int i = 0; i < 2; i++){
        free(symbol_xpm_map[i]);
    }

    for(int i = 0; i < 2; i++){
        free(menu_xpm_map[i]);
    }

    for(int i = 0; i < 26; i++){
        free(letters_xpm_map[i]);
    }
}

void (drawLetter)(char letter, uint16_t x, uint16_t y) {
    int index = letter - 'a';
    draw_xpm(letters_xpm[index], letters_xpm_map[index], x, y);
}

void (drawNumber)(int number, uint16_t x, uint16_t y) {
    draw_xpm(numbers_xpm[number], numbers_xpm_map[number], x, y);
}

void (drawString)(char string[], uint16_t x, uint16_t y) {
    for (size_t i = 0; i < strlen(string); i++) {
        if (string[i] == ':')
            draw_xpm(symbol_xpm[1], symbol_xpm_map[1], x + i * letterSpacing, y);
            
        drawLetter(string[i], x + i * letterSpacing, y);
    }
}


