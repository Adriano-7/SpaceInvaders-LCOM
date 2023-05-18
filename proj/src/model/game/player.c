
#include "model/game/player.h"

extern vbe_mode_info_t mode_info;

Player* createPlayer(GameObject* gameObject) {
  Player* player = malloc(sizeof(Player));
  if (player == NULL) {
    printf("Error: malloc failed in createPlayer\n");
    exit(EXIT_FAILURE);
  }

  player->canShoot = true;
  player->lives = 3;
  player->score = 0;
  player->gameObject = gameObject;

  return player;
}

void movePlayer(Player* player, enum Direction direction) {
  player->gameObject->old_x = player->gameObject->x;
    player->gameObject->old_y = player->gameObject->y;
    
  switch (direction) {
    case LEFT:
      if (player->gameObject->x - player->gameObject->speed >= 0) {
        player->gameObject->x -= player->gameObject->speed;
      }
      break;
    case RIGHT:
      if (player->gameObject->x + player->gameObject->speed + player->gameObject->img.width < mode_info.XResolution) {
        player->gameObject->x += player->gameObject->speed;
      }
      break;
    default:
      break;
  }
}

