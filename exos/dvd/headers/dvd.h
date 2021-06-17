#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

#define DVDSIZE_W 117
#define DVDSIZE_H 68
#define MOVE 10

typedef struct point_t {
    int x;
    int y;
} point_t;
typedef struct dvd_t {
    struct point_t coo[2];
    int speed;
    int precSpeed;
    int dx;
    int dy;
    int prevText;
    int currText;
    int windowMovingSpeed;
} dvd_t;

void completeArray();

void drawCircle(SDL_Point *, int, int, int);

void drawBall(SDL_Renderer *, int, int, int);

void drawDVD(SDL_Renderer *, SDL_Texture *, int, int);

void moveWindowUp(SDL_Window *,int speed);

void moveWindowDown(SDL_Window *, SDL_DisplayMode,int speed);

void moveWindowLeft(SDL_Window *,int speed);

void moveWindowRight(SDL_Window *, SDL_DisplayMode,int speed);

#endif //SNAKE_SNAKE_H
