#include "../headers/animation.h"
#include "../headers/graphics.h"
#include <string.h>

void drawOneFrame(SDL_Rect *frames, SDL_Texture *texture, SDL_Renderer *renderer,
                  int currentFrame, SDL_Point point, int cellW, int cellH, int flipped) {
    SDL_Rect dest = {0};
    dest.w = (cellW)/2;
    dest.h = (cellH)/2;
    dest.x = point.x + cellW/2 - dest.w/2;
    dest.y = point.y + cellH/2 - dest.h/2;
    SDL_Point center = {dest.x + dest.w / 2, dest.y + dest.h / 2};

    if (!flipped) {
        SDL_RenderCopy(renderer, texture, frames + currentFrame, &dest);
    } else {
        SDL_RenderCopyEx(renderer, texture, frames + currentFrame, &dest, 0, &center, SDL_FLIP_HORIZONTAL);
    }

}

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
