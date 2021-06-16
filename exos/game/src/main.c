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
	SDL_RenderPresent(renderer);
	SDL_Delay(10);
	
        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            printf("UP\n");
                            // JUMP
                            break;
                        case SDLK_LEFT:
                            printf("LEFT\n");
                            // MARCHE GAUCHE
                            break;
                        case SDLK_RIGHT:
                            printf("RIGHT\n");
                            // MARCHE DROITE
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
        SDL_Delay(10);

    }
    return 0;
}
