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

int main() {
    initGraphics();
    SDL_Window * window = createWindow(0, 0, 450, 800);
    SDL_Renderer * renderer = createRenderer(window);
    SDL_Texture * texture = IMG_LoadTexture(renderer, "../data/ninja.png");
    SDL_Texture * texture2 = IMG_LoadTexture(renderer, "../data/bg.svg");
    SDL_Rect * frames = loadAnimationPos(2, 9, 300, 300);
    while(1) {
        drawAnimationLoop(frames, 9, texture, texture2, 10, window, renderer);
    }
}