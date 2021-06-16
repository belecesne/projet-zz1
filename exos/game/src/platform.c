#include "../headers/platform.h"

void createOnePlatform(SDL_Renderer *renderer, SDL_Texture * texture, int x, int y){
	SDL_Rect source = {0};
	SDL_Rect platform = {x, y, 150, 100};
	SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
	SDL_RenderCopy(renderer, texture, &source, &platform);
}

void createAllPlatforms(SDL_Renderer * renderer, SDL_Texture * texture, SDL_Point * coordArray){
	int x, y, i;
	for(i = 0; i < 7; i++){
		x = coordArray[i].x;
		y = coordArray[i].y;
		createOnePlatform(renderer, texture, x, y);
	}
}
