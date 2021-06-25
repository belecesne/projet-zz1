#include "../headers/move.h"


void deplacement(SDL_Point * pointDepart, SDL_Point * pointArrivee, int cellW, int cellH){
	int pas;
	if(pointDepart->y == pointArrivee->y && pointDepart->x < pointArrivee->x){
		pas = cellW / 12 * 2;
		pointDepart->x += pas;
	}
	else if(pointDepart->y == pointArrivee->y && pointDepart->x > pointArrivee->x){
		pas = cellW / 12 * 2;
		pointDepart->x -= pas;
	}
	else if(pointDepart->x == pointArrivee->x && pointDepart->y < pointArrivee->y){
		pas = cellH / 12 * 2;
		pointDepart->y += pas;
	}
	else if(pointDepart->x == pointArrivee->x && pointDepart->y > pointArrivee->y){
		pas = cellH / 12 * 2;
		pointDepart->y -= pas;
	}
}

void drawMove(SDL_Renderer * renderer, SDL_Point point, int cellW, int cellH) {
	SDL_Rect rect;
	rect.x = point.x;
	rect.y = point.y;
	rect.w = cellW;
	rect.h = cellH;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
