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
    int speed, currentTexture = (rand() % 7), prevText, precSpeed;
    texture[0] = IMG_LoadTexture(snakeRender, "data/dvd_blanc.png");
    texture[1] = IMG_LoadTexture(snakeRender, "data/dvd_bleu.png");
    texture[2] = IMG_LoadTexture(snakeRender, "data/dvd_jaune.png");
    texture[3] = IMG_LoadTexture(snakeRender, "data/dvd_orange.png");
    texture[4] = IMG_LoadTexture(snakeRender, "data/dvd_rose.png");
    texture[5] = IMG_LoadTexture(snakeRender, "data/dvd_rouge.png");
    texture[6] = IMG_LoadTexture(snakeRender, "data/dvd_vert.png");


    completeArray();
    int x = (rand() % WINDOW_W), y = (rand() % WINDOW_H), posX = (rand() % 2), posY = (rand() % 2), dx, dy;
    speed = SPEED;
    precSpeed = SPEED;
    if (x < 117) {
        x += 117;
    } else if (x > WINDOW_W - 117) {
        x -= 117;
    }
    if (y < 68) {
        y += 68;
    } else if (y > WINDOW_H - 68) {
        y -= 68;
    }
    switch (posX) {
        case 1:
            dx = 1;

            break;
        case 0:
            dx = -1;
            break;
    }
    switch (posY) {
        case 1:
            dy = 1;
            break;
        case 0:
            dy = -1;
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
                            y += precSpeed * dy;
                            break;
                        case SDLK_DOWN:
                            y -= precSpeed * dy;
                            break;
                        case SDLK_LEFT:
                            x -= precSpeed * dx;
                            break;
                        case SDLK_RIGHT:
                            x += precSpeed * dx;
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

        drawDVD(snakeRender, texture[currentTexture], x, y);
        SDL_RenderPresent(snakeRender);
        SDL_RenderClear(snakeRender);

        if (x + dx > WINDOW_W - 117 || x + dx < 0) {
            dx = -dx;
            prevText = currentTexture;
            while (prevText == currentTexture) {
                currentTexture = (rand() % 7);
            }
        }
        if (y + dy > WINDOW_H - 68 || y + dy < 0) {
            dy = -dy;
            prevText = currentTexture;
            while (prevText == currentTexture) {
                currentTexture = (rand() % 7);
            }
        }
        x += speed * dx;
        y += speed * dy;

        SDL_Delay(1);
    }

    endSdl(1, "Fermeture Normale", snakeWindow, snakeRender);
    return 0;
}