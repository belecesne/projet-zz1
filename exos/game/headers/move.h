#ifndef GAME_ZZ1_MOVE_H
#define GAME_ZZ1_MOVE_H
#include <SDL2/SDL.h>
#include "player.h"
#define SPEED 20
#define JUMPSPEED 4

void moveUp(player_t *);
void moveLeft(player_t *);
void moveRight(int,player_t *);
void moveDown(int, player_t *);
void jump(player_t *);
int collision(player_t*, SDL_Point *);
#endif //GAME_ZZ1_MOVE_H c
