#include "../headers/graphics.h"



SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
	SDL_Texture* my_texture;

	my_texture = IMG_LoadTexture(renderer,"./img/Maze.png");
	if (my_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

	return my_texture;
}

void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer) {
	SDL_Rect
			source = {0},                         // Rectangle définissant la zone de la texture à récupérer
	window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
	destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

	SDL_GetWindowSize(
			window, &window_dimensions.w,
			&window_dimensions.h);                    // Récupération des dimensions de la fenêtre
	SDL_QueryTexture(my_texture, NULL, NULL,
	                 &source.w, &source.h);       // Récupération des dimensions de l'image

	destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

	/* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

	SDL_RenderCopy(renderer, my_texture,
	               &source,
	               &destination);                 // Création de l'élément à afficher
	SDL_RenderPresent(renderer);                  // Affichage
	SDL_Delay(2000);                              // Pause en ms

	SDL_RenderClear(renderer);                    // Effacer la fenêtre
}

IMG_Quit()