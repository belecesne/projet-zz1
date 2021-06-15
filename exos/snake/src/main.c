#include "../headers/main.h"


int main(int *argc, char *argv[]) {
    SDL_DisplayMode disp;
    SDL_Window *snakeWindow;
    SDL_Texture *texture[7];
    SDL_Renderer *snakeRender;
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    snakeWindow = createWindow(100, 100, WINDOW_W, WINDOW_H);
    snakeRender = createRenderer(snakeWindow);
    srand(time(NULL));
    int speed, currentTextureDVD1 = (rand() % 7), prevTextDVD1, precSpeed, currentTextureDVD2 = (rand() %
                                                                                                 7), prevTextDVD2;
    texture[0] = IMG_LoadTexture(snakeRender, "data/dvd_blanc.png");
    texture[1] = IMG_LoadTexture(snakeRender, "data/dvd_bleu.png");
    texture[2] = IMG_LoadTexture(snakeRender, "data/dvd_jaune.png");
    texture[3] = IMG_LoadTexture(snakeRender, "data/dvd_orange.png");
    texture[4] = IMG_LoadTexture(snakeRender, "data/dvd_rose.png");
    texture[5] = IMG_LoadTexture(snakeRender, "data/dvd_rouge.png");
    texture[6] = IMG_LoadTexture(snakeRender, "data/dvd_vert.png");


    completeArray();
    int xDVD1 = (rand() % WINDOW_W), yDVD1 = (rand() % WINDOW_H), posXDVD1 = (rand() % 2), posYDVD1 = (rand() %
                                                                                                       2), dxDVD1, dyDVD1;
    speed = SPEED;
    precSpeed = SPEED;
    if (xDVD1 < 117) {
        xDVD1 += 117;
    } else if (xDVD1 > WINDOW_W - 117) {
        xDVD1 -= 117;
    }
    if (yDVD1 < 68) {
        yDVD1 += 68;
    } else if (yDVD1 > WINDOW_H - 68) {
        yDVD1 -= 68;
    }
    switch (posXDVD1) {
        case 1:
            dxDVD1 = 1;

            break;
        case 0:
            dxDVD1 = -1;
            break;
    }
    switch (posYDVD1) {
        case 1:
            dyDVD1 = 1;
            break;
        case 0:
            dyDVD1 = -1;
            break;
    }


    int xDVD2 = (rand() % WINDOW_W), yDVD2 = (rand() % WINDOW_H), posXDVD2 = (rand() % 2), posYDVD2 = (rand() %
                                                                                                       2), dxDVD2, dyDVD2;
    speed = SPEED;
    precSpeed = SPEED;
    if (xDVD2 < 117) {
        xDVD2 += 117;
    } else if (xDVD2 > WINDOW_W - 117) {
        xDVD2 -= 117;
    }
    if (yDVD2 < 68) {
        yDVD2 += 68;
    } else if (yDVD2 > WINDOW_H - 68) {
        yDVD2 -= 68;
    }
    switch (posXDVD2) {
        case 1:
            dxDVD2 = 1;

            break;
        case 0:
            dxDVD2 = -1;
            break;
    }
    switch (posYDVD2) {
        case 1:
            dyDVD2 = 1;
            break;
        case 0:
            dyDVD2 = -1;
            break;
    }


    SDL_bool program_on = SDL_TRUE;
    while (program_on) {
        SDL_Event event;
        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            yDVD1 += precSpeed * dyDVD1;
                            break;
                        case SDLK_DOWN:
                            yDVD1 -= precSpeed * dyDVD1;
                            break;
                        case SDLK_LEFT:
                            xDVD1 -= precSpeed * dxDVD1;
                            break;
                        case SDLK_RIGHT:
                            xDVD1 += precSpeed * dxDVD1;
                            break;
                        case SDLK_z:
                            yDVD2 -= precSpeed * dyDVD2;
                            break;
                        case SDLK_s:
                            yDVD2 += precSpeed * dyDVD2;
                            break;
                        case SDLK_q:
                            xDVD2 -= precSpeed * dxDVD2;
                            break;
                        case SDLK_d:
                            xDVD2 += precSpeed * dxDVD2;
                            break;
                        case SDLK_a:
                            if (speed > 1) {
                                speed--;
                                precSpeed--;
                            }
                            break;
                        case SDLK_e:
                            if (speed < 20) {
                                speed++;
                                precSpeed++;
                            }
                            break;
                        case SDLK_SPACE:

                            if (speed) {
                                precSpeed = speed;
                                speed = 0;
                            } else {
                                speed = precSpeed;
                            }
                            break;
                    }
                default:
                    break;
            }

        }


        SDL_RenderClear(snakeRender);

        drawDVD(snakeRender, texture[currentTextureDVD1], xDVD1, yDVD1);
        SDL_Delay(5);
        drawDVD(snakeRender, texture[currentTextureDVD2], xDVD2, yDVD2);
        SDL_RenderPresent(snakeRender);


        if (xDVD1 + dxDVD1 > WINDOW_W - 117 || xDVD1 + dxDVD1 < 0) {
            dxDVD1 = -dxDVD1;
            prevTextDVD1 = currentTextureDVD1;
            while (prevTextDVD1 == currentTextureDVD1) {
                currentTextureDVD1 = (rand() % 7);
            }
        }
        if (yDVD1 + dyDVD1 > WINDOW_H - 68 || yDVD1 + dyDVD1 < 0) {
            dyDVD1 = -dyDVD1;
            prevTextDVD1 = currentTextureDVD1;
            while (prevTextDVD1 == currentTextureDVD1) {
                currentTextureDVD1 = (rand() % 7);
            }
        }

        if (xDVD2 + dxDVD2 > WINDOW_W - 117 || xDVD2 + dxDVD2 < 0) {
            dxDVD2 = -dxDVD2;
            prevTextDVD2 = currentTextureDVD2;
            while (prevTextDVD2 == currentTextureDVD2) {
                currentTextureDVD2 = (rand() % 7);
            }
        }
        if (yDVD2 + dyDVD2 > WINDOW_H - 68 || yDVD2 + dyDVD2 < 0) {
            dyDVD2 = -dyDVD2;
            prevTextDVD2 = currentTextureDVD2;
            while (prevTextDVD2 == currentTextureDVD2) {
                currentTextureDVD2 = (rand() % 7);
            }
        }
        xDVD1 += speed * dxDVD1;
        yDVD1 += speed * dyDVD1;
        xDVD2 += speed * dxDVD2;
        yDVD2 += speed * dyDVD2;
        SDL_Delay(2);
    }
    for(int i = 0; i < 7; i++) {
        SDL_DestroyTexture(texture[i]);
    }
    endSdl(1, "Fermeture Normale", snakeWindow, snakeRender);
    return 0;
}