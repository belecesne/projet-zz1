#ifndef ANIMATION
#define ANIMATION

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.h"

void drawOneFrame(SDL_Rect *, SDL_Texture * , SDL_Renderer * , int  , player_t *, int);
SDL_Rect * loadAnimationPos(int , int , int , int );

#endif
