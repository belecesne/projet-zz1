#include "../headers/move.h"


int deplacement(SDL_Point * pointDepart, SDL_Point * pointArrivee, int cellW, int cellH){
	int retour = 5, pas;
	if(pointDepart->y == pointArrivee->y && pointDepart->x < pointArrivee->x){
		pas = cellW / 12 * 2;
		pointDepart->x += pas;
		retour = 1;
	}
	else if(pointDepart->y == pointArrivee->y && pointDepart->x > pointArrivee->x){
		pas = cellW / 12 * 2;
		pointDepart->x -= pas;
		retour = 2;
	}
	else if(pointDepart->x == pointArrivee->x && pointDepart->y < pointArrivee->y){
		pas = cellH / 12 * 2;
		pointDepart->y += pas;
		retour = 3;
	}
	else if(pointDepart->x == pointArrivee->x && pointDepart->y > pointArrivee->y){
		pas = cellH / 12 * 2;
		pointDepart->y -= pas;
		retour = 4;
	}
	return retour;
}

void drawMove(SDL_Renderer * renderer, SDL_Point point, int cellW, int cellH, int direction, SDL_Texture * textureCarre, SDL_Rect ** frames, int * currentFrame) {
	switch (direction) {
		case 1:
			drawOneFrame(frames[0], textureCarre, renderer, *currentFrame, point, cellW, cellH, 0);
			(*currentFrame) = ((*currentFrame) + 1) % 6;
			break;
		case 2:
			drawOneFrame(frames[0], textureCarre, renderer, *currentFrame, point, cellW, cellH, 1);
			(*currentFrame) = ((*currentFrame) + 1) % 6;
			break;
		case 3:
			drawOneFrame(frames[1], textureCarre, renderer, *currentFrame, point, cellW, cellH, 0);
			(*currentFrame)++;
			break;
		case 4:
			drawOneFrame(frames[1], textureCarre, renderer, 11 - *currentFrame, point, cellW, cellH, 0);
			(*currentFrame)++;
			break;
		case 5:
			drawOneFrame(frames[2], textureCarre, renderer, *currentFrame, point, cellW, cellH, 0);
			break;
		default:
			break;
	}
}
