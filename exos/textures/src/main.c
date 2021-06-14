#include <stdio.h>
#include "../headers/graphics.h"



int main(int argc, char **argv) {
    
    initGraphics();
    
    SDL_DisplayMode disp;
    SDL_GetCurrentDisplayMode(0, &disp);
    SDL_Window ** matrix = createWindowMatrix(20);
    initMatrix(matrix, 20, disp.w, disp.h);

    /* Normalement, on devrait ici remplir les fenêtres... */
    SDL_Delay(2000);                           // Pause exprimée  en ms

    shiftWindows(matrix, 20, disp.w, disp.h, 15, 30);

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    destroyMatrix(matrix, 20);

    SDL_Quit();
    return 0;
}
