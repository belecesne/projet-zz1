#include "../headers/textures.h"

SDL_Rect *loadAnimationPos(int line, int numberColumns, int lineHeight, int columnWidth) {
	SDL_Rect *frames = malloc(numberColumns * sizeof(SDL_Rect));
	int yCurr = line * lineHeight, xCurr = 0;
	for (int i = 0; i < numberColumns; i++) {
		frames[i].x = xCurr;
		frames[i].y = yCurr;
		frames[i].w = columnWidth;
		frames[i].h = lineHeight;
		xCurr += columnWidth;
	}
	return frames;
}

void drawOneFrame(SDL_Rect *frames, SDL_Texture *texture, SDL_Renderer *renderer,
                  int currentFrame, SDL_Rect dest, int flipped) {
	dest.w = 100;
	dest.h = 100;
	SDL_Point center = {dest.x + dest.w / 2, dest.y + dest.h / 2};

	if (!flipped) {
		SDL_RenderCopy(renderer, texture, frames + currentFrame, &dest);
	} else {
		SDL_RenderCopyEx(renderer, texture, frames + currentFrame, &dest, 0, &center, SDL_FLIP_HORIZONTAL);
	}

}
