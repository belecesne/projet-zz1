#include "../headers/main.h"
#include "../headers/platform.h"


int main(int argc, char *argv[]) {
    srand(time(NULL));

    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(10, 10, WINDOW_W, WINDOW_H);
    renderer = createRenderer(window);
    player_t player = {{250, 500, 100, 100}, SPEED, JUMPTIME, 0, 1, 1};
    SDL_bool program_on = SDL_TRUE;
	SDL_Texture * plat1 = IMG_LoadTexture(renderer, "data/plat1.png"); 
	int i;

	SDL_Point coordArray[8] = {{0, 100},
				{150, 200},
				{300, 300},
				{0, 400},
				{150, 500},
				{300, 600},
				{0, 700}};
    while (program_on) {
        SDL_Event event;
	SDL_RenderClear(renderer);
	createAllPlatforms(renderer, plat1, coordArray);
	nextPlatform(coordArray, window);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	
        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            printf("UP\n");
                            printf("isJumping : %d - jumpTime : %d\n", player.isJumping, player.jumpTime);
                            if (!player.isJumping) {
                                player.isJumping = 1;
                            }

                            //moveUp(&player);
                            // JUMP
                            break;
                        case SDLK_LEFT:
                            printf("LEFT\n");
                            moveLeft(&player);
                            break;
                        case SDLK_RIGHT:
                            printf("RIGHT\n");
                            moveRight(WINDOW_W, &player);
                            // MARCHE DROITE
                            break;
                        case SDLK_DOWN:
                            printf("DOWN\n");
                            moveDown(WINDOW_H, &player);
                            // BAS
                            break;
                        case SDLK_r:
                            printf("R\n");
                            // reinit
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }


        if (player.isJumping) {
            if (player.jumpTime >= JUMPTIME) {
                player.isJumping = 0;
                player.jumpTime = 0;
                player.dy = 0;
            } else {
                jump(&player);
            }
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &(player.rect));
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
	endSdl(1, "Fermeture normale", window, renderer);
    return 0;
}
