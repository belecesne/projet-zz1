#ifndef GAME_ZZ1_PLAYER_H
#define GAME_ZZ1_PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct player_t {
    SDL_Rect rect;
    int dy;
    int onPlateform;
}player_t;
#endif //GAME_ZZ1_PLAYER_H
