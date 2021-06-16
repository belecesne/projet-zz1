#include "../headers/move.h"



void moveLeft(SDL_Rect * rect) {
    if(rect->x > 0) {
        (rect->x)-=SPEED;
    }
}

void moveRight(int weight, SDL_Rect * rect) {
    if((rect->x + rect->w)< weight) {
        (rect->x)+=SPEED;
    }
}

void moveUp(SDL_Rect * rect) {
    if(rect->y > 0) {
        (rect->y)-=SPEED;
    }
}

void moveDown(int height, SDL_Rect * rect) {
    if((rect->y +rect->h) < height) {
        (rect->y)+=SPEED;
    }
}