#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>

void initGraphics();
SDL_Window * createWindow(int xPos, int yPos, int width, int height);
SDL_Window *** createWindowMatrix(int length);
void initMatrix(SDL_Window *** matrix, int length, int screen_width, int screen_height);
void destroyMatrix(SDL_Window*** matrix, int length);
#endif