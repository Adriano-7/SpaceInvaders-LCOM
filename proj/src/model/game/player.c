
#include "model/game/player.h"

extern vbe_mode_info_t mode_info;

extern xpm_image_t game_xpm[4];
extern uint8_t* game_xpm_map[4];

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

