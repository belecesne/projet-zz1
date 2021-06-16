#include "../headers/main.h"


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
    while (program_on) {
        SDL_Event event;
        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
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