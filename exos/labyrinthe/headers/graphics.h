#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_W 800
#define WINDOW_H 800

void initGraphics();
SDL_Window * createWindow(int, int, int, int);
SDL_Renderer * createRenderer(SDL_Window *);
void endSdl(char,char const*, SDL_Window*, SDL_Renderer*);
#endif