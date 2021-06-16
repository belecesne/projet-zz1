#ifndef ANIMATION
#define ANIMATION

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.h"

void drawAnimationLoop(SDL_Rect *, int, SDL_Texture *, SDL_Texture *, int, SDL_Window *, SDL_Renderer *);
void drawOneFrame(SDL_Rect * , int , SDL_Texture * , SDL_Window * , SDL_Renderer * , int  , player_t *, int);
SDL_Rect * loadAnimationPos(int , int , int , int );

#endif
