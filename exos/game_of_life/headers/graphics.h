#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>

void initGraphics();

SDL_Window* createWindow(int, int, int, int);

SDL_Renderer* createRenderer(SDL_Window*);

void drawMatrix(SDL_Renderer*, SDL_Window*, int[][GAME_LENGTH], int);

void end_sdl(char, char const*, SDL_Window*, SDL_Renderer*);

int getPosFromMouse(int, int, int*, int*, SDL_Window*, int);

#endif
