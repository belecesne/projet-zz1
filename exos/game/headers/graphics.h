#ifndef GAME_ZZ1_GRAPHICS_H
#define GAME_ZZ1_GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

void initGraphics();
SDL_Window * createWindow(int, int, int, int);
SDL_Renderer * createRenderer(SDL_Window *);
void endSdl(char,char const*, SDL_Window*, SDL_Renderer*);

#endif //GAME_ZZ1_GRAPHICS_H
