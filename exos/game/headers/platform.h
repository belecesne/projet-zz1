#ifndef PROJETTZZ1_GAME_PLATFORM_H
#define PROJETTZZ1_GAME_PLATFORM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct platform_c{
	SDL_Point coordArray[7];
	int head;
	int size;
} platform_t;

void createOnePlatform(SDL_Renderer *, SDL_Texture *, int, int);
void createAllPlatforms(SDL_Renderer *, SDL_Texture *, platform_t *);
void nextPlatform(platform_t *, SDL_Window *);


#endif //PROJETTZZ1_GAME_PLATFORM_H
