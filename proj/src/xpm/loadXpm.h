#pragma once
#include <lcom/lcf.h>
#include "../devices/video.h"
#include "gameXpm.h"
#include "lettersXpm.h"
#include "menuXpm.h"
#include "numbersXpm.h"
#include "symbolsXpm.h"

static const int letterSpacing = 25;

static const xpm_row_t *game_xpm_name[] = {nave_xpm, osvaldo_xpm, osvaldo_xpm1, ivan_xpm, ivan_xpm1, miro_xpm, miro_xpm1, bullet_xpm, heart_xpm};
static const xpm_row_t *symbol_xpm_name[] = {two_points_xpm, cursor_xpm, bar_xpm};
static const xpm_row_t *menu_xpm_name[] = {logotipo_xpm, playgame_xpm, highScore_xpm, quitGame_xpm, leaderboard_xpm};
static const xpm_row_t *letters_xpm_name[] = {a_xpm, b_xpm, c_xpm, d_xpm, e_xpm, f_xpm, g_xpm, h_xpm, i_xpm, j_xpm, k_xpm, l_xpm, m_xpm, n_xpm, o_xpm, p_xpm, q_xpm, r_xpm, s_xpm, t_xpm, u_xpm, v_xpm, w_xpm, x_xpm, y_xpm, z_xpm};
static const xpm_row_t *numbers_xpm_name[] = {zero_xpm, one_xpm, two_xpm, three_xpm, four_xpm, five_xpm, six_xpm, seven_xpm, eight_xpm, nine_xpm};

xpm_image_t game_xpm[9];
xpm_image_t symbol_xpm[3];
xpm_image_t menu_xpm[5];
xpm_image_t letters_xpm[26];
xpm_image_t numbers_xpm[10];

uint8_t* game_xpm_map[9];
uint8_t* symbol_xpm_map[3];
uint8_t* menu_xpm_map[5];
uint8_t* letters_xpm_map[26];
uint8_t* numbers_xpm_map[10];

void (drawLetter)(char letter, uint16_t x, uint16_t y);
void (drawNumber)(int number, uint16_t x, uint16_t y);
void (drawString)(char string[], uint16_t x, uint16_t y);


void loadXpms();
