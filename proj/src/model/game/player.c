
#include "model/game/player.h"

extern vbe_mode_info_t mode_info;


Player_t* createPlayer(int speedX) {
  Player_t* player = malloc(sizeof(Player_t));
  if (player == NULL) {
    printf("Error: malloc failed in createPlayer\n");
    exit(EXIT_FAILURE);
  }

  xpm_image_t img[2];
  uint8_t* img_colors[2];

  img[0] = game_xpm[0];
  img_colors[0] = game_xpm_map[0];

  img[1] = game_xpm[0];
  img_colors[1] = game_xpm_map[0];

  player->canShoot = true;
  player->lives = 3;
  player->score = 10;
  player->drawableObject = createdrawableObject((mode_info.XResolution/2)-(game_xpm[0].width/2), mode_info.YResolution-game_xpm[0].height-30, img ,img_colors,true);
  player->speedX = speedX;

  return player;
}

void destroyPlayer(Player_t* player) {
  free(player->drawableObject);
  free(player);
}
