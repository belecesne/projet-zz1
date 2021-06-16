#ifndef GAME_ZZ1_PLAYER_H
#define GAME_ZZ1_PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define JUMPTIME 350
typedef struct player_t {
    SDL_Rect rect;
    int dx;
    int dy;
    int isJumping;
    int jumpTime;
    int onPlatform;
}player_t;
#endif //GAME_ZZ1_PLAYER_H
