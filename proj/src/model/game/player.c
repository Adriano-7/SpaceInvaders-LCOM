
#include "model/game/player.h"

extern vbe_mode_info_t mode_info;

extern xpm_image_t game_xpm[4];
extern uint8_t* game_xpm_map[4];

extern xpm_image_t symbol_xpm[1];
extern uint8_t* symbol_xpm_map[1];

Player_t* createPlayer() {
  Player_t* player = malloc(sizeof(Player_t));
  if (player == NULL) {
    printf("Error: malloc failed in createPlayer\n");
    exit(EXIT_FAILURE);
  }

  player->canShoot = true;
  player->lives = 3;
  player->score = 0;
  player->gameObject = createGameObject((mode_info.XResolution/2)-(game_xpm[0].width/2), mode_info.YResolution-game_xpm[0].height-30, 30, 0, game_xpm[0] ,game_xpm_map[0],true);

  return player;
}

void destroyPlayer(Player_t* player) {
  free(player->gameObject);
  free(player);
}

void drawLiveBar(Player_t* player) {
  for (int i = 0; i < player->lives; i++) {
    // I want to draw it on the top right corner of the screen
    draw_xpm(symbol_xpm[0], symbol_xpm_map[0], mode_info.XResolution - (i+1)*symbol_xpm[0].width - mode_info.XResolution / 40, mode_info.YResolution / 40);
  }
}
