#include "../headers/move.h"


void deplacement(SDL_Point * pointDepart, SDL_Point * pointArrivee, int pasW, int pasH){
    if(pointDepart->y == pointArrivee->y && pointDepart->x < pointArrivee->x){
        pointDepart->x += pasW;
    }
    else if(pointDepart->y == pointArrivee->y && pointDepart->x > pointArrivee->x){
        pointDepart->x -= pasW;
    }
    else if(pointDepart->x == pointArrivee->x && pointDepart->y < pointArrivee->y){
        pointDepart->y += pasH;
    }
    else if(pointDepart->x == pointArrivee->x && pointDepart->y > pointArrivee->y){
        pointDepart->y -= pasH;
    }
}

void drawMoveProfondeur(SDL_Renderer * renderer, SDL_Point point, int cellW, int cellH) {
    SDL_Rect rect;
    rect.w = cellW/2;
    rect.h = cellH/2;
    rect.x = point.x+(rect.w)/2;
    rect.y = point.y+(rect.h)/2;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}

void drawMove(SDL_Renderer * renderer, SDL_Point point, int cellW, int cellH) {
    SDL_Rect rect;
    rect.w = cellW/2;
    rect.h = cellH/2;
    rect.x = point.x+(rect.w)/2;
    rect.y = point.y+(rect.h)/2;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

}