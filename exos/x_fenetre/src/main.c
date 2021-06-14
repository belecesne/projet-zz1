#include <stdio.h>
#include "../headers/graphics.h"



int main(int argc, char **argv) {
    
    initGraphics();
    
    SDL_Window *** matrix = createWindowMatrix(10);
    initMatrix(matrix, 10, 1920, 1080);

    /* Normalement, on devrait ici remplir les fenêtres... */
    SDL_Delay(2000);                           // Pause exprimée  en ms

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    destroyMatrix(matrix, 10);

    SDL_Quit();
    return 0;
}
