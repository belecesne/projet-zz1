#ifndef ANIMATION
#define ANIMATION

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void drawOneFrame(SDL_Rect *, SDL_Texture *, SDL_Renderer *,
                  int, SDL_Point, int , int , int);
SDL_Rect * loadAnimationPos(int , int , int , int );

#endif
