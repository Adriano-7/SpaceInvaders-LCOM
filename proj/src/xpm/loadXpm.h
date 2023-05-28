/**
 * @file loadXpm.h
 * @brief Functions for loading and drawing XPM images.
 */

#pragma once

#include <lcom/lcf.h>
#include "../devices/video.h"
#include "gameXpm.h"
#include "lettersXpm.h"
#include "menuXpm.h"
#include "numbersXpm.h"
#include "symbolsXpm.h"
#include "gameoverXpm.h"

/**
 * @brief The spacing between letters when drawing a string.
 */
static const int letterSpacing = 25;

/**
 * @brief Array of XPM images used in the game.
 */
static const xpm_row_t *game_xpm_name[] = {nave_xpm, osvaldo_xpm, osvaldo_xpm1, ivan_xpm, ivan_xpm1, miro_xpm, miro_xpm1, bullet_xpm, heart_xpm};
/**
 * @brief Array of XPM images for symbols used in the game.
 */
static const xpm_row_t *symbol_xpm_name[] = {two_points_xpm, cursor_xpm, bar_xpm};
/**
 * @brief Array of XPM images for menu elements.
 */
static const xpm_row_t *menu_xpm_name[] = {logotipo_xpm, playgame_xpm, highScore_xpm, quitGame_xpm, leaderboard_xpm};
/**
 * @brief Array of XPM images for letters of the alphabet.
 */
static const xpm_row_t *letters_xpm_name[] = {a_xpm, b_xpm, c_xpm, d_xpm, e_xpm, f_xpm, g_xpm, h_xpm, i_xpm, j_xpm, k_xpm, l_xpm, m_xpm, n_xpm, o_xpm, p_xpm, q_xpm, r_xpm, s_xpm, t_xpm, u_xpm, v_xpm, w_xpm, x_xpm, y_xpm, z_xpm};
/**
 * @brief Array of XPM images for numbers.
 */
static const xpm_row_t *numbers_xpm_name[] = {zero_xpm, one_xpm, two_xpm, three_xpm, four_xpm, five_xpm, six_xpm, seven_xpm, eight_xpm, nine_xpm, yellow_zero_xpm, yellow_one_xpm, yellow_two_xpm, yellow_three_xpm, yellow_four_xpm, yellow_five_xpm, yellow_six_xpm, yellow_seven_xpm, yellow_eight_xpm, yellow_nine_xpm};
/**
 * @brief Array of XPM images for game over screen elements.
 */
static const xpm_row_t *gameover_xpm_name[] = {gamoverlogo_xpm, scored_xpm, playagain_xpm, mainmenu_xpm};

/**
 * @brief Array of loaded XPM images for game elements.
 */
xpm_image_t game_xpm[9];
/**
 * @brief Array of loaded XPM images for symbol elements.
 */
xpm_image_t symbol_xpm[3];
/**
 * @brief Array of loaded XPM images for menu elements.
 */
xpm_image_t menu_xpm[5];
/**
 * @brief Array of loaded XPM images for letters.
 */
xpm_image_t letters_xpm[26];
/**
 * @brief Array of loaded XPM images for numbers.
 */
xpm_image_t numbers_xpm[20];
/**
 * @brief Array of loaded XPM images for game over screen elements.
 */
xpm_image_t gameover_xpm[4];

/**
 * @brief Array of pointers to the pixel map of game XPM images.
 */
uint8_t* game_xpm_map[9];
/**
 * @brief Array of pointers to the pixel map of symbol XPM images.
 */
uint8_t* symbol_xpm_map[3];
/**
 * @brief Array of pointers to the pixel map of menu XPM images.
 */
uint8_t* menu_xpm_map[5];
/**
 * @brief Array of pointers to the pixel map of letter XPM images.
 */
uint8_t* letters_xpm_map[26];
/**
 * @brief Array of pointers to the pixel map of number XPM images.
 */
uint8_t* numbers_xpm_map[20];
/**
 * @brief Array of pointers to the pixel map of game over XPM images.
 */
uint8_t* gameover_xpm_map[4];

/**
 * @brief Draw a letter XPM image at the specified position.
 * 
 * @param letter The letter to be drawn.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 */
void drawLetter(char letter, uint16_t x, uint16_t y);

/**
 * @brief Draw a number XPM image at the specified position.
 * 
 * @param number The number to be drawn.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 */
void drawNumber(int number, uint16_t x, uint16_t y, bool yellow);

/**
 * @brief Draw a string of letters at the specified position.
 * 
 * @param string The string to be drawn.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 */
void drawString(char string[], uint16_t x, uint16_t y);

/**
 * @brief Load all XPM images into memory.
 */
void loadXpms();

/*
    * @brief Clean all XPM images from memory.
*/
void cleanXpms();
