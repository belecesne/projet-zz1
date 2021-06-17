#include "../headers/platform.h"

void createOnePlatform(SDL_Renderer *renderer, SDL_Texture * texture, int x, int y){
	SDL_Rect source = {0};
	SDL_Rect platform = {x, y, 150, 100};
	SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
	SDL_RenderCopy(renderer, texture, &source, &platform);
}

void createAllPlatforms(SDL_Renderer * renderer, SDL_Texture * texture, platform_t * platforms){
	int x, y, i = platforms->head, n = platforms->size;
	while((i + 1) % n != platforms->head){
		x = platforms.coordArray[i].x;
		y = platforms.coordArray[i].y;
		createOnePlatform(renderer, texture, x, y);
		i = (i + 1) % n;
	}
}

void nextPlatform(platform_t * platforms, SDL_Window * window){
	int winWidth, winHeight;
	SDL_GetWindowSize(window, &winWidth, &winHeight);
	int columnWidth = winWidth / 3;
	int column = rand() % 3;
	int x = column * columnWidth;
	coordArray[platforms->head].x = x;
	coordArray[platforms->head].y = 100;
	platforms->head = (platforms->head + 1) % platforms->size;
}
