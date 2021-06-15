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
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                            printf("UP\n");
                            y+= SPEED*dy;
                            break;
                        case SDLK_DOWN:
                            printf("DOWN\n");
                            y-=SPEED*dy;
                            break;
                        case SDLK_LEFT:
                            printf("LEFT\n");
                            x-=SPEED*dx;
                            break;
                        case SDLK_RIGHT:
                            printf("RIGHT\n");
                            x+=SPEED*dx;
                            break;
                    }
                default:
                    break;
            }

        }
        for(int i = 0; i < 15; i++) {
            drawBall(snakeRender, x, y, BALL_RADIUS);
            SDL_RenderPresent(snakeRender);
            SDL_SetRenderDrawColor(snakeRender, 0, 0, 0, 255);
            SDL_RenderClear(snakeRender);

            if (x + dx > WINDOW_W - BALL_RADIUS || x + dx < BALL_RADIUS) {
                dx = -dx;
            }
            if (y + dy > WINDOW_H - BALL_RADIUS || y + dy < BALL_RADIUS) {
                dy = -dy;
            }

            x += SPEED*dx;
            y += SPEED*dy;
        }
        SDL_Delay(10);
    }

    endSdl(1, "Fermeture Normale", snakeWindow, snakeRender);
    return 0;
}