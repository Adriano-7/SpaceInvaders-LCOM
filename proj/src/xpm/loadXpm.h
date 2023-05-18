#include <lcom/lcf.h>
#include "../devices/graphics.h"
#include "gameXpm.h"
#include "lettersXpm.h"
#include "menuXpm.h"
#include "numbersXpm.h"

static const xpm_row_t *game_xpm_name[] = {nave_xpm, osvaldo_xpm, ivan_xpm, miro_xpm};
static const xpm_row_t *menu_xpm_name[] = {highScore_xpm, quitGame_xpm};
static const xpm_row_t *letters_xpm_name[] = {a_xpm, b_xpm, c_xpm, d_xpm, e_xpm, f_xpm, g_xpm, h_xpm, i_xpm, j_xpm, k_xpm, l_xpm, m_xpm, n_xpm, o_xpm, p_xpm, q_xpm, r_xpm, s_xpm, t_xpm, u_xpm, v_xpm, w_xpm, x_xpm, y_xpm, z_xpm};
//static const xpm_row_t *numbers_xpm_name[] = {zero_xpm, one_xpm, two_xpm, three_xpm, four_xpm, five_xpm, six_xpm, seven_xpm, eight_xpm, nine_xpm};

xpm_image_t game_xpm[4];
xpm_image_t menu_xpm[2];
xpm_image_t letters_xpm[26];
xpm_image_t numbers_xpm[10];

uint8_t* game_xpm_map[4];
uint8_t* menu_xpm_map[2];
uint8_t* letters_xpm_map[26];
//static uint8_t* numbers_xpm_map[10];

void loadXpms();
void cleanXpms();
