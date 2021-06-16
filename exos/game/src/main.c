#include "../headers/main.h"


int main(int argc, char *argv[]) {
    srand(time(NULL));

    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect sourceBg = {0}, destBg = {0};

    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(10, 10, WINDOW_W, WINDOW_H);
    renderer = createRenderer(window);
    player_t player = {{0, 500, 100, 100}, SPEED, JUMPHEIGH, 0, 1, 1, 0};
    SDL_bool program_on = SDL_TRUE;
    SDL_Texture *plat1 = IMG_LoadTexture(renderer, "data/plat1.png");


    SDL_Texture *texture = IMG_LoadTexture(renderer, "./data/ninja.png");
    SDL_Texture *background = IMG_LoadTexture(renderer, "./data/bg.svg");
    SDL_Rect *framesSaut = loadAnimationPos(2, 9, 300, 300);
    SDL_Rect *framesStatic = loadAnimationPos(0, 5, 300, 300);
    SDL_Rect *framesRun = loadAnimationPos(1, 6, 300, 300);
    SDL_QueryTexture(background, NULL, NULL, &sourceBg.w, &sourceBg.h);
    SDL_GetWindowSize(window, &destBg.w, &destBg.h);

    int i, currentFrameRun = 0, currentFrameIdle = 0,flipped = 0;

    SDL_Point coordArray[8] = {{0,   100},
                               {150, 200},
                               {300, 300},
                               {0,   400},
                               {150, 500},
                               {300, 600},
                               {0,   700}};
    while (program_on) {
        SDL_Event event;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, &sourceBg, &destBg);
        createAllPlatforms(renderer, plat1, coordArray);


        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            if (!player.isJumping) {
                                player.isJumping = 1;
                            }

                            // JUMP
                            break;
                        case SDLK_LEFT:
                            flipped = 1;
                            player.dx = -1;
                            player.isMoving = 1;

                            moveLeft(&player);
                            drawOneFrame(framesRun, 6, texture, window, renderer, currentFrameRun, &player,flipped);
                            currentFrameRun = (currentFrameRun + 1) % 6;
                            break;
                        case SDLK_RIGHT:
                            flipped = 0;
                            player.dx = 1;
                            player.isMoving = 1;
                            
                            moveRight(WINDOW_W, &player);
                            //drawAnimationLoop(framesRun, 6, texture, background, 10,window,renderer);
                            drawOneFrame(framesRun, 6, texture, window, renderer, currentFrameRun, &player,flipped);
                            currentFrameRun = (currentFrameRun + 1) % 6;
                            // MARCHE DROITE
                            break;
                        case SDLK_r:
                            // reinit
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }



        if (!player.isMoving) {
            printf("Joueur au repos : affichage frame\n");
            drawOneFrame(framesStatic, 5, texture, window, renderer, currentFrameIdle, &player,flipped);
            i++;

            if (i == 6) {
                currentFrameIdle = (currentFrameIdle + 1) % 5;
                i = 0;
            }
        }
        player.isMoving = 0;
        printf("Le joueur saute ? %d\n",player.isJumping);
        if (player.isJumping) {
            if (player.jumpTime >= JUMPHEIGH) {
                player.jumpTime = 0;
                player.dy = 0;
                player.isJumping = 0;

            } else {
                printf("Saut : %d\n",player.jumpTime);
                jump(&player);
            }
        }

        //int coll = collision(&player, coordArray);

        // Plateforme
        //nextPlatform(coordArray, window);

        // Saut
/*
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &(player.rect));
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
*/
        SDL_RenderPresent(renderer);
        SDL_Delay(30);
        //player.isMoving = 0;
    }
    endSdl(1, "Fermeture normale", window, renderer);
    return 0;
}
