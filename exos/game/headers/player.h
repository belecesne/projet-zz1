#ifndef GAME_ZZ1_PLAYER_H
#define GAME_ZZ1_PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define JUMPLENGTH 320// HAUTEUR DE SAUT DIVISBLE PAR DEUX SINON ERREUR ( Hauteur = 2* longueur du saut)
#define SPEED 1
#define JUMPSPEED 5
#define DX 5

typedef struct player_t {
    SDL_Rect rect;
    int dx;
    int dy;
    int isJumping;
    int jumpTime;
    int canJump;
	int isMoving;
}player_t;
#endif //GAME_ZZ1_PLAYER_H
