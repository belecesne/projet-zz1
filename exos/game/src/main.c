#include "../headers/main.h"


int main(int argc, char * argv[]) {
    srand(time(NULL));

    SDL_DisplayMode disp;
    SDL_Window * window;
    SDL_Renderer *renderer;
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(10, 10, WINDOW_W, WINDOW_H);
    renderer = createRenderer(window);
    SDL_Delay(3000);
    return 0;
}