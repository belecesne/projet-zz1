#include "../headers/main.h"


int main(int * argc, char *argv[]) {
    SDL_DisplayMode disp;
    SDL_Window * snakeWindow;
    SDL_Renderer * snakeRender;
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    snakeWindow = createWindow(100,100,disp.w/(1.5),disp.h/(1.5));

    snakeRender = createRenderer(snakeWindow);
    drawSnake(snakeRender,500,500,30,70,255,0,0);

    SDL_Delay(5000);
    endSdl(1, "Fermeture Normale", snakeWindow, snakeRender);
    return 0;
}