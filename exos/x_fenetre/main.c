#include <stdio.h>
#include "graphics.h"



int main(int argc, char **argv) {
    
    initGraphics();
    
    SDL_Window * win1 = createWindow(0, 0, 400, 800);

    /* Normalement, on devrait ici remplir les fenêtres... */
    SDL_Delay(2000);                           // Pause exprimée  en ms

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    SDL_DestroyWindow(win1);

    SDL_Quit();
    return 0;
}