#include "bullet.h"

Bullet_t* createBullet(int x, int y, int speedY, enum DirectionY direction, enum BulletType type){
    Bullet_t* bullet = malloc(sizeof(Bullet_t));
    if (bullet == NULL) {
        printf("Error: malloc failed in createBullet\n");
        exit(EXIT_FAILURE);
    }

    xpm_image_t img = game_xpm[7];
    uint8_t* img_colors = game_xpm_map[7];

    bullet->drawableObject = createdrawableObject(x, y, img , img_colors, false);
    bullet->speedY = speedY;
    bullet->direction = direction;
    bullet->type = type;

    return bullet;
}

void fireBullet(Bullet_t* bullet, DrawableObject_t* shooter, enum DirectionY direction){    
    if(bullet->drawableObject->isVisible == false && shooter->isVisible == true){
        bullet->drawableObject->x = shooter->x + (shooter->img.width/2) - (bullet->drawableObject->img.width/2);

        if(direction == UP){
            bullet->drawableObject->y = shooter->y - bullet->drawableObject->img.height;
        }

        else if(direction == DOWN){
            bullet->drawableObject->y = shooter->y + shooter->img.height;
        }

        bullet->drawableObject->old_x = bullet->drawableObject->x;
        bullet->drawableObject->old_y = bullet->drawableObject->y;

        bullet->drawableObject->isVisible = true;
    }
}

void destroyBullet(Bullet_t* bullet){
    free(bullet->drawableObject);
    free(bullet);
}
