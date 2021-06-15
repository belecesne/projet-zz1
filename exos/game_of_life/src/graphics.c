#include "../headers/graphics.h"

void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                  char const* msg,                                    // message à afficher
                  SDL_Window* window,                                 // fenêtre à fermer
                  SDL_Renderer* renderer) {                           // renderer à fermer
  char msg_formated[255];                                         
  int l;                                                          

  if (!ok) {                                                      
         strncpy(msg_formated, msg, 250);                                 
         l = strlen(msg_formated);                                        
         strcpy(msg_formated + l, " : %s\n");                     

         SDL_Log(msg_formated, SDL_GetError());                   
  }                                                               

  if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
  if (window != NULL)   SDL_DestroyWindow(window);                                        

  SDL_Quit();                                                     

  if (!ok) {                                                      
         exit(EXIT_FAILURE);                                              
  }                                                               
}  

void initGraphics() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
}

SDL_Window * createWindow(int xPos, int yPos, int width, int height) {
    SDL_Window * window = SDL_CreateWindow("SDL Window", xPos, yPos, width, height, SDL_WINDOW_RESIZABLE);  
    if (window == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        end_sdl(0, "ERROR WINDOW CREATION", window, NULL);
    }
    return window;
}

SDL_Renderer * createRenderer(SDL_Window * window) {
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_Log("Error : SDL renderer creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
    }
    return renderer;
}

void drawMatrix(SDL_Renderer * renderer, SDL_Window * window, int game[][30], int gameLength) {
    SDL_Rect bg;
    int screen_width, screen_height;
    SDL_GetWindowSize(window, &screen_width, &screen_height);
    bg.x = 0;
    bg.y = 0;
    bg.w = screen_width;
    bg.h = screen_height;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &bg);
    const int rect_width = screen_width / gameLength;
    const int rect_height = screen_height / gameLength;
    int curr_pos_x, curr_pos_y = 0;
    for(int i = 0; i < gameLength; i++) {
        for(int j = 0; j < gameLength; j++) {
            SDL_Rect rect;
            rect.x = curr_pos_x;
            rect.y = curr_pos_y;
            rect.w = rect_width;
            rect.h = rect_height;
            if(!game[i][j]) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
            curr_pos_x += rect_width;
        }
        curr_pos_x = 0;
        curr_pos_y += rect_height;
    }
}    