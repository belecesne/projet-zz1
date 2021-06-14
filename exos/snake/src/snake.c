#include "../headers/snake.h"

void drawSnake(SDL_Renderer *renderer, int x, int y, int w, int h, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    int sizeW,sizeH,currX,currY;
    sizeW = w;
    sizeH = h;
    currX = x;
    currY = y;
    for (int i = 0; i <10;i++) {
        SDL_RenderDrawLine(renderer, currX, currY, currX + sizeW, currY);
        SDL_RenderDrawLine(renderer, currX + sizeW, currY, currX + sizeW, currY + sizeH);
        SDL_RenderDrawLine(renderer, currX, currY + sizeH, currX + sizeW, currY + sizeH);
        SDL_RenderDrawLine(renderer, currX, currY, currX, currY + sizeH);
        SDL_RenderPresent(renderer);
    }

}