#include "../headers/main.h"


int main(int * argc, char *argv[]) {
    SDL_DisplayMode disp;
    SDL_Window * snakeWindow;
    SDL_Renderer * snakeRender;
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    snakeWindow = createWindow(100,100,700,700);
    snakeRender = createRenderer(snakeWindow);
    srand(time(NULL));
    completeArray();
    int x = (rand()%WINDOW_W),y = (rand()%WINDOW_H),posX = (rand()%2),posY = (rand()%2),dx,dy;
    if (x < 50)
    {
        x+=50;
    }
    else if (x >WINDOW_W - 50)
    {
        x-=50;
    }
    if (y < 50)
    {
        y+=50;
    }
    else if (y > WINDOW_H - 50)
    {
        y-=50;
    }
    printf("%d - %d\n",x,y);
    switch(posX){
        case 1:
            dx = 1;
            break;
        case 0:
            dx = -1;
            break;
    }
    switch(posY){
        case 1:
            dy = 1;
            break;
        case 0:
            dy = -1;
            break;
    }
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
        SDL_SetRenderDrawColor(snakeRender,0, 0, 0, 255);
        SDL_RenderClear(snakeRender);

        x+=10;
        SDL_Delay(50);
    }

    endSdl(1, "Fermeture Normale", snakeWindow, snakeRender);
    return 0;
}