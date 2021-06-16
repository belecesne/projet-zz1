#ifndef GAME_ZZ1_MOVE_H
#define GAME_ZZ1_MOVE_H
#include <SDL2/SDL.h>
#define SPEED 20

void moveUp(SDL_Rect *);
void moveLeft(SDL_Rect *);
void moveRight(int,SDL_Rect *);
void moveDown(int, SDL_Rect *);

#endif //GAME_ZZ1_MOVE_H
