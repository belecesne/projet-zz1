#ifndef PROJETTZZ1_GAME_PLATFORM_H
#define PROJETTZZ1_GAME_PLATFORM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void createOnePlatform(SDL_Renderer *, SDL_Texture *, int, int);
void createAllPlatforms(SDL_Renderer *, SDL_Texture *, SDL_Point *);


#endif //PROJETTZZ1_GAME_PLATFORM_H
