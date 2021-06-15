#include "../headers/main.h"


int main(int * argc, char *argv[]) {
    SDL_DisplayMode disp;
    SDL_Window * snakeWindow;
    SDL_Renderer * snakeRender;
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    snakeWindow = createWindow(100,100,700,700);
    snakeRender = createRenderer(snakeWindow);
    completeArray();
    int x = 100,y = 100;
    SDL_bool program_on = SDL_TRUE;
    while (program_on){
        SDL_Event event;
        while(program_on && SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                default:
                    break;
            }

        }
        drawBall(snakeRender,x,y);
        SDL_RenderPresent(snakeRender);
        SDL_SetRenderDrawColor(snakeRender,255, 0, 0, 255);
        x+=10;
        SDL_Delay(50);
    }

    endSdl(1, "Fermeture Normale", snakeWindow, snakeRender);
    return 0;
}