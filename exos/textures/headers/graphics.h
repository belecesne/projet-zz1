#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>

SDL_Texture* load_texture_from_image(char  *, SDL_Window *, SDL_Renderer *);
void play_with_texture_1(SDL_Texture *, SDL_Window *, SDL_Renderer *);
#endif