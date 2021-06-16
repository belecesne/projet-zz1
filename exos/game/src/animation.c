 #include "../headers/animation.h"
 #include "../headers/graphics.h"
 #include <string.h>

void drawAnimationLoop(SDL_Rect * frames, int nb_frames, SDL_Texture * texture, SDL_Texture * background, int frameRate, SDL_Window * window, SDL_Renderer * renderer) {
    SDL_Rect source = {0}, dest = {0}, sourceBg = {0}, destBg = {0};
    dest.w = 100;
    dest.h = 100;
    SDL_QueryTexture(background, NULL, NULL, &sourceBg.w, &sourceBg.h);
    SDL_GetWindowSize(window, &destBg.w, &destBg.h);
    for(int i = 0; i < nb_frames; i++) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, &sourceBg, &destBg);
        SDL_RenderCopy(renderer, texture, frames + i, &dest);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/frameRate);
    }
}

void drawOneFrame(SDL_Rect * frames, int nb_frames, SDL_Texture * texture, SDL_Window * window, SDL_Renderer * renderer, int * currentFrame, player_t * player) {
    SDL_Rect source = {0}, dest = {0};
dest.x = player->rect.x;
dest.y = player->rect.y;
    dest.w = 100;
    dest.h = 100;
    SDL_RenderCopy(renderer, texture, frames + *currentFrame, &dest);
	*currentFrame = (*currentFrame + 1) % nb_frames;
}

SDL_Rect * loadAnimationPos(int line, int numberColumns, int lineHeight, int columnWidth) {
    SDL_Rect * frames = malloc(numberColumns * sizeof(SDL_Rect));
    int yCurr = line*lineHeight, xCurr = 0;
    for(int i = 0; i < numberColumns; i++) {
        frames[i].x = xCurr;
        frames[i].y = yCurr;
        frames[i].w = columnWidth;
        frames[i].h = lineHeight;
        xCurr += columnWidth;
    }
    return frames;
}
