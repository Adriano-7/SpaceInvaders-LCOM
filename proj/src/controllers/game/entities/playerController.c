#include "playerController.h"

void movePlayer(Player_t* player, enum DirectionX direction) {
  if(player == NULL) {
    printf("Error: player is NULL in movePlayer\n");
    exit(EXIT_FAILURE);
  }
  
  player->drawableObject->old_x = player->drawableObject->x;
  player->drawableObject->old_y = player->drawableObject->y;
    
  switch (direction) {
    case LEFT:
      printf("moving LEFT\n");
      if (player->drawableObject->x - player->speedX >= 0) {
        player->drawableObject->x -= player->speedX;
      }
      break;
    case RIGHT:
      printf("moving RIGHT\n");
      if (player->drawableObject->x + player->speedX + player->drawableObject->img.width < mode_info.XResolution) {
        player->drawableObject->x += player->speedX;
      }
      break;
    default:
      break;
  }
}

