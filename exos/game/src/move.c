#include "../headers/move.h"



void moveLeft(player_t * player) {
    if(((player->rect.x) - SPEED) > 0) {
        (player->rect.x)-=SPEED;
    }
    else if(((player->rect.x)) > 0) {
        (player->rect.x) = 0;
    }
}

void moveRight(int weight, player_t * player) {
    if(((player->rect.x) + player->rect.w + SPEED)< weight) {
        (player->rect.x)+=SPEED;
    }
    else if(((player->rect.x) + player->rect.w)< weight) {
        (player->rect.x)=(weight - player->rect.w);
    }
}

void moveUp(player_t * player) {
    if(((player->rect.y) - SPEED) > 0) {
        (player->rect.y)-=SPEED;
    }
    else if(((player->rect.y) + player->rect.h) > 0) {
        (player->rect.y) = 0;
    }
}

void moveDown(int height, player_t * player) {
    if(((player->rect.y) + player->rect.h + SPEED)< height) {
        (player->rect.y)+=SPEED;
    }
    else if(((player->rect.y) + player->rect.h)< height) {
        (player->rect.y)=(height - player->rect.h);
    }
}