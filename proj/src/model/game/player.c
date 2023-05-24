#include "model/game/player.h"

extern vbe_mode_info_t mode_info;


Player_t* createPlayer(int speedX) {
  Player_t* player = malloc(sizeof(Player_t));
  if (player == NULL) {
    printf("Error: malloc failed in createPlayer\n");
    exit(EXIT_FAILURE);
  }

  xpm_image_t img = game_xpm[0];
  uint8_t* img_colors = game_xpm_map[0];

  player->lives = 3;
  player->score = 0;
  player->drawableObject = createdrawableObject((mode_info.XResolution/2)-(game_xpm[0].width/2), mode_info.YResolution-game_xpm[0].height-30, img ,img_colors,true);
  player->speedX = speedX;

  return player;
}

void destroyPlayer(Player_t* player) {
  free(player->drawableObject);
  free(player);
}

