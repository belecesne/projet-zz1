#include "../headers/move.h"


void moveLeft(player_t *player) {
    if (((player->rect.x) - SPEED) > 0) {
        (player->rect.x) += (player->dx)*SPEED;
    } else if (((player->rect.x)) > 0) {
        (player->rect.x) = 0;
    }
}

void moveRight(int weight, player_t *player) {
    if (((player->rect.x) + player->rect.w + SPEED) < weight) {
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
	if((xPlayer >= xCurrentPlat - 33 && xPlayer <= xCurrentPlat + 117) && yPlayer + 100 <= yCurrentPlat + 48 && yPlayer + 100 >= yCurrentPlat +40){
		printf("Courant\n");
		return 0;
	} else if((xPlayer >= xNextPlat - 33 && xPlayer <= xNextPlat + 117) && yPlayer + 100 <= yNextPlat + 48 && yPlayer + 100 >= yNextPlat +40){
		printf("saut réussi\n");
		return 1;
	} else {
		printf("tombé\n");
		return -1;
	}
}
