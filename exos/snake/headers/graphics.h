#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>

void initGraphics();
SDL_Window * createWindow(int, int, int, int);
SDL_Renderer * createRenderer(SDL_Window *);
void endSdl(char,char const*, SDL_Window*, SDL_Renderer*);
#endif