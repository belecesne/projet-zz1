#include "../headers/move.h"


void moveLeft(player_t *player) {
    if (((player->rect.x) + (player->dx)*SPEED) > 0) {
        (player->rect.x) += (player->dx)*SPEED;
    } else if (((player->rect.x)) > 0) {
        (player->rect.x) = 0;
    }
}

void moveRight(int weight, player_t *player) {
    if (((player->rect.x) + player->rect.w + (player->dx)*SPEED) < weight) {
        (player->rect.x) += (player->dx)*SPEED;
    } else if (((player->rect.x) + player->rect.w) < weight) {
        (player->rect.x) = (weight - player->rect.w);
    }
}


void jump(player_t *player) {
    if (player->jumpTime < (JUMPLENGTH / 2)) {
        player->dy = -1;
    } else {
        player->dy = 1;
    }
    if (player->isJumping) {
        player->jumpTime+=JUMPSPEED;
        player->rect.y = player->rect.y + JUMPSPEED * player->dy;
    }

}

int collision(player_t* player, SDL_Point *coordArray){
	int xPlayer = player->rect.x;
	int yPlayer = player->rect.y;
	int xCurrentPlat = coordArray[6].x;
	int yCurrentPlat = coordArray[6].y;
	int xNextPlat = coordArray[5].x;
	int yNextPlat = coordArray[5].y;
	if((xPlayer + 100 >= xCurrentPlat + 33 && xPlayer <= xCurrentPlat + 117) && yPlayer + 100 <= yCurrentPlat + 48 && yPlayer + 100 >= yCurrentPlat +40 && player->dy >= 0){
		return 1;
	} else if((xPlayer + 100 >= xNextPlat + 33 && xPlayer <= xNextPlat + 117) && yPlayer + 100 <= yNextPlat + 48 && yPlayer + 100 >= yNextPlat +40 && player->dy > 0){
		return 2;
	} else if(player->isJumping){
		return 3;
	} else {
		return 0;
	}
}
