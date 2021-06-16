 #include "../headers/animation.h"
 #include "../headers/graphics.h"
 #include <string.h>

void drawAnimationLoop(SDL_Texture ** frames, int nb_frames, SDL_Texture * background, int frameRate, SDL_Window * window, SDL_Renderer * renderer) {
    SDL_Rect source = {0}, dest = {0}, sourceBg = {0}, destBg = {0};
    dest.w = 100;
    dest.h = 100;
    SDL_QueryTexture(background, NULL, NULL, &sourceBg.w, &sourceBg.h);
    SDL_GetWindowSize(window, &destBg.w, &destBg.h);
    for(int i = 0; i < nb_frames; i++) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, &sourceBg, &destBg);
        SDL_QueryTexture(frames[i], NULL, NULL, &source.w, &source.h);
        SDL_RenderCopy(renderer, frames[i], &source, &dest);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/frameRate);
    }
}

int main() {
    initGraphics();
    SDL_Window * window = createWindow(0, 0, 450, 800);
    SDL_Renderer * renderer = createRenderer(window);
    SDL_Texture * texture2 = IMG_LoadTexture(renderer, "../data/bg.svg");
    SDL_Texture ** frames = malloc(10* sizeof(SDL_Texture *));
    char name[50];
    for(int i = 1; i <= 6; i++) {
        sprintf(name, "../data/ninja_run_%d.png", i);
        frames[i-1] = IMG_LoadTexture(renderer, name);
    }
    while(1) {
        SDL_RenderClear(renderer);
        drawAnimationLoop(frames, 6, texture2, 25, window, renderer);
    }
}