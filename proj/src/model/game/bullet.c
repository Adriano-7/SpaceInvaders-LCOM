#include "bullet.h"

Bullet_t* createBullet(int x, int y, int speedX){
    Bullet_t* bullet = malloc(sizeof(Bullet_t));
    if (bullet == NULL) {
        printf("Error: malloc failed in createBullet\n");
        exit(EXIT_FAILURE);
    }

  xpm_image_t img[2];
  uint8_t* img_colors[2];

  img[0] = game_xpm[7];
  img_colors[0] = game_xpm_map[7];

  img[1] = game_xpm[0];
  img_colors[1] = game_xpm_map[7];

    bullet->drawableObject = createdrawableObject(x, y, img ,img_colors,false);
    bullet->direction = UP;
    bullet->speedY = speedX;

    return bullet;
}

void fireBullet(Bullet_t* bullet, int x, int y, enum DirectionY direction){
    printf("Firing bullet\n");
    
    bullet->drawableObject->x = x;
    bullet->drawableObject->y = y;
    bullet->direction = direction;
    bullet->drawableObject->isVisible = true;
}

void destroyBullet(Bullet_t* bullet){
    free(bullet->drawableObject);
    free(bullet);
}
