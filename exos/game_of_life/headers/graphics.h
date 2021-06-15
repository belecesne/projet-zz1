#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>

void initGraphics();
SDL_Window * createWindow(int xPos, int yPos, int width, int height);
SDL_Renderer * createRenderer(SDL_Window * window);
void drawMatrix(SDL_Renderer * renderer, SDL_Window * window, int game[][30], int gameLength);
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);

#endif