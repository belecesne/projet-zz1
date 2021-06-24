#ifndef PROJET_ZZ1_MOVE_H
#define PROJET_ZZ1_MOVE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "animation.h"

int deplacement(SDL_Point*, SDL_Point*, int, int);

void drawMove(SDL_Renderer*, SDL_Point, int, int, int, SDL_Texture*, SDL_Rect**, int*);


#endif //PROJET_ZZ1_MOVE_H
