#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>

void initGraphics();
SDL_Window * createWindow(int xPos, int yPos, int width, int height);
#endif