#ifndef GAME_ZZ1_MOVE_H
#define GAME_ZZ1_MOVE_H
#include <SDL2/SDL.h>
#include "player.h"
#include "platform.h"


void moveLeft(player_t *);
void moveRight(int,player_t *);
void jump(player_t *);
int collision(player_t*, platform_t *);
#endif //GAME_ZZ1_MOVE_H c
