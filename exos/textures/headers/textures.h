#ifndef PROJET_ZZ1_TEXTURES_H
#define PROJET_ZZ1_TEXTURES_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

SDL_Rect *loadAnimationPos(int, int, int, int);
void drawOneFrame(SDL_Rect *, SDL_Texture *, SDL_Renderer *, int, SDL_Rect, int);

#endif //PROJET_ZZ1_TEXTURES_H
