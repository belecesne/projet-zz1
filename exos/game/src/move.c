#include "../headers/move.h"


void moveLeft(player_t *player) {
    if (((player->rect.x) - SPEED) > 0) {
        (player->rect.x) -= SPEED;
    } else if (((player->rect.x)) > 0) {
        (player->rect.x) = 0;
    }
}

void moveRight(int weight, player_t *player) {
    if (((player->rect.x) + player->rect.w + SPEED) < weight) {
        (player->rect.x) += SPEED;
    } else if (((player->rect.x) + player->rect.w) < weight) {
        (player->rect.x) = (weight - player->rect.w);
    }
}

void moveUp(player_t *player) {
    if (((player->rect.y) - SPEED) > 0) {
        (player->rect.y) -= SPEED;
    } else if (((player->rect.y) + player->rect.h) > 0) {
        (player->rect.y) = 0;
    }
}

void moveDown(int height, player_t *player) {
    if (((player->rect.y) + player->rect.h + SPEED) < height) {
        (player->rect.y) += SPEED;
    } else if (((player->rect.y) + player->rect.h) < height) {
        (player->rect.y) = (height - player->rect.h);
    }
}

void jump(player_t *player) {
    if (player->jumpTime < (JUMPTIME / 2)-1) {
        player->dy = -1;
    } else {
        player->dy = 1;
    }
    if (player->isJumping) {
        player->jumpTime += JUMPSPEED;
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
	if((xPlayer >= xCurrentPlat - 33 && xPlayer <= xCurrentPlat + 117) && !player->isJumping && yPlayer + 100 <= yCurrentPlat + 44){
		printf("%d %d\n", yPlayer, yCurrentPlat);
		return 0;
	} else if((xPlayer >= xNextPlat - 33 && xPlayer <= xNextPlat + 117) && yPlayer + 100 <= yNextPlat + 44){
		printf("saut réussi\n");
		return 1;
	} else {
		printf("tombé\n");
		return -1;
	}
}
