
#include "model/game/player.h"

extern vbe_mode_info_t mode_info;


Player_t* createPlayer() {
  Player_t* player = malloc(sizeof(Player_t));
  if (player == NULL) {
    printf("Error: malloc failed in createPlayer\n");
    exit(EXIT_FAILURE);
  }

  player->canShoot = true;
  player->lives = 3;
  player->score = 10;
  player->gameObject = createGameObject((mode_info.XResolution/2)-(game_xpm[0].width/2), mode_info.YResolution-game_xpm[0].height-30, 30, 0, game_xpm[0] ,game_xpm_map[0],true);

  return player;
}

void destroyPlayer(Player_t* player) {
  free(player->gameObject);
  free(player);
}

void drawLiveBar(Player_t* player) {
  for (int i = 0; i < player->lives; i++) {
    draw_xpm(symbol_xpm[0], symbol_xpm_map[0], mode_info.XResolution - (i+1)*symbol_xpm[0].width - mode_info.XResolution / 40, mode_info.YResolution / 40);
  }
}

void drawScore(Player_t* player){
  drawString("score:", mode_info.XResolution / 40, mode_info.YResolution / 40);
  int score = player->score;
  int digits = 0;
  while (score != 0) {
    score /= 10;
    digits++;
  }
  score = player->score;
  int tempScore = score;

for (int i = digits - 1; i >= 0; i--) {
    int currentDigit = tempScore % 10;
    draw_xpm(numbers_xpm[currentDigit], numbers_xpm_map[currentDigit], mode_info.XResolution / 40 + 7 * letters_xpm[0].width + i * numbers_xpm[0].width, mode_info.YResolution / 40);
    tempScore /= 10;
}
}
