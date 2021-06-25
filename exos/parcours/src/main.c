#include "../headers/graph.h"
#include "../headers/labyrinthe.h"
#include "../headers/graphics.h"
#include "../headers/cellule.h"
#include "../headers/dijkstra.h"
#include "../headers/a_etoile.h"
#include "../headers/dfs.h"
#include "../headers/draw_parcours.h"
#include "../headers/file.h"
#include "../headers/move.h"
#include <time.h>

#define LIGNE 10
#define COLONNE 10
#define SEED 1624566722

int main(){
	int tailleCellW, tailleCellH, enParcours = 0, delay, max_delay = 5, posPile, direction, currentFrame = 0;
	cellule_t* cellCourante;
	noeud_t* parentDest;
	file_t* fileParcours;
	SDL_DisplayMode disp;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* textureMur, * textureSol, * textureSortie, * textureEntree, * textureCarre, * textureSolGris;
	SDL_Rect* framesCarre[3];
	SDL_Point ptDep, ptArr;
	int window_w, window_h, offset, t;
	tailleCellH = (WINDOW_H / (LIGNE * 2 + 1));
	tailleCellW = (WINDOW_W / (COLONNE * 2 + 1));
	window_w = (tailleCellW) * (COLONNE * 2 + 1);
	window_h = (tailleCellH) * (LIGNE * 2 + 1);
	printf("Taille de la fenêtre : %d - %d\n", window_w, window_h);
	long int seed = SEED;
	srand(seed);
	printf("GRAINE DE GENERATION DE LA FONCTION ALEATOIRE : %ld\n", seed);
	labyrinthe_t* labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE, tailleCellW, tailleCellH, 0.1);
	parentDest = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
	initGraphics();
	const char* titles[] = {"Dijkstra .", "Dijkstra . .", "Dijkstra . . .", "A* Euclidienne .", "A* Euclidienne . .",
	                        "A* Euclidienne . . .", "A* Tchebychev .", "A* Tchebychev . .", "A* Tchebychev . . .",
	                        "A* Manhattan .", "A* Manhattan . .", "A* Manhattan . . .", "DFS .", "DFS . .", "DFS . . .",
	                        "Labyrinthe", "Labyrinthe", "Labyrinthe"};
	offset = 15, t = 0;
	SDL_GetCurrentDisplayMode(0, &disp);
	window = createWindow(10, 10, window_w, window_h);
	renderer = createRenderer(window);
	textureMur = IMG_LoadTexture(renderer, "data/wall.png");
	textureSol = IMG_LoadTexture(renderer, "data/ground.png");
	textureSolGris = IMG_LoadTexture(renderer, "data/groundGrey.png");
	textureEntree = IMG_LoadTexture(renderer, "data/entree.png");
	textureSortie = IMG_LoadTexture(renderer, "data/sortie.png");
	textureCarre = IMG_LoadTexture(renderer, "./data/carre2.png");

	framesCarre[0] = loadAnimationPos(0, 6, 50, 50);
	framesCarre[1] = loadAnimationPos(1, 12, 50, 50);
	framesCarre[2] = loadAnimationPos(0, 1, 50, 50);

	SDL_bool program_on = SDL_TRUE;
	while(program_on){
		if(delay == max_delay){
			SDL_SetWindowTitle(window, titles[offset + (++t % 3)]);
		}
		SDL_Event event;
		SDL_RenderClear(renderer);
		drawLabyrinthe(renderer, labyrinthe, window_w, window_h, textureMur,
		               textureSol, textureEntree, textureSortie, textureSolGris);
		if(enParcours && enParcours != 5){
			if(file_est_vide(fileParcours)){
				if(enParcours != 3 && enParcours != 4){
					enParcours = 5;
					cellCourante = labyrinthe->tableauCellules[parentDest[posPile]];
					posPile--;
					ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
					ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
					ptArr = ptDep;
					delay = 0;
					drawMove(renderer, ptDep, tailleCellW, tailleCellH, 5, textureCarre, framesCarre, &currentFrame);
					currentFrame = 0;

				} else{
					enParcours = 4;
				}
			} else{
				switch(enParcours){
					case 1:
						if(delay == max_delay){
							drawParcours(renderer, cellCourante, labyrinthe->tableauCellules,
							             labyrinthe->colonnes);
							cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
							defiler(fileParcours);
							delay = 0;
						}
						drawMove(renderer, ptDep, tailleCellW, tailleCellH, 5, textureCarre, framesCarre,
						         &currentFrame);
						delay++;
						break;
					case 2:
						if(delay == max_delay){
							drawParcours(renderer, cellCourante, labyrinthe->tableauCellules,
							             labyrinthe->colonnes);
							cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
							defiler(fileParcours);
							delay = 0;
						}
						drawMove(renderer, ptDep, tailleCellW, tailleCellH, 5, textureCarre, framesCarre,
						         &currentFrame);
						delay++;
						break;
					case 3:
						if(delay >= 12){
							ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
							ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
							drawParcours(renderer, cellCourante, labyrinthe->tableauCellules,
							             labyrinthe->colonnes);
							cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
							defiler(fileParcours);
							ptArr.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
							ptArr.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
							delay = 0;
							currentFrame = 0;
						}
						delay++;
						drawMove(renderer, ptDep, tailleCellW, tailleCellH, direction, textureCarre, framesCarre,
						         &currentFrame);
						direction = deplacement(&ptDep, &ptArr, tailleCellW, tailleCellH);
						break;
					default:
						break;
				}
			}
		}
		if(enParcours == 4){
			offset = 15;
			currentFrame = 0;
			delay = max_delay;
			drawMove(renderer, ptArr, tailleCellW, tailleCellH, 5, textureCarre, framesCarre, &currentFrame);
		} else if(enParcours == 5){

			if(delay >= 12 && posPile > -1){
				ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
				ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
				drawParcours(renderer, cellCourante, labyrinthe->tableauCellules,
				             labyrinthe->colonnes);
				cellCourante = labyrinthe->tableauCellules[parentDest[posPile]];
				posPile--;
				ptArr.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
				ptArr.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
				delay = 0;
				currentFrame = 0;
			}
			drawMove(renderer, ptDep, tailleCellW, tailleCellH, direction, textureCarre, framesCarre, &currentFrame);

			direction = deplacement(&ptDep, &ptArr, tailleCellW, tailleCellH);
			if(delay >= 12 && posPile == -1){
				enParcours = 4;
			}
			delay++;

		}
		while(program_on && SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT :
					program_on = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_r:
							if(enParcours == 0 || enParcours == 4){
								offset = 0;
								enParcours = 1;
								delay = 0;
								printf("Dijkstra\n");
								labyrinthe->entree = labyrinthe->sortie;
								labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								while(labyrinthe->sortie == labyrinthe->entree){
									labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = dijkstra(labyrinthe, labyrinthe->entree, labyrinthe->sortie, parentDest,
								                        &posPile);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
								defiler(fileParcours);

							}
							break;
						case SDLK_a:
							if(enParcours == 0 || enParcours == 4){
								offset = 3;
								enParcours = 2;
								delay = 0;
								printf("A* Euclidienne\n");
								labyrinthe->entree = labyrinthe->sortie;
								labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								while(labyrinthe->sortie == labyrinthe->entree){
									labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = a_etoile(labyrinthe, labyrinthe->entree, distEuclidienne,
								                        labyrinthe->sortie, labyrinthe->colonnes, parentDest, &posPile);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
								defiler(fileParcours);


							}
							break;
						case SDLK_z:
							if(enParcours == 0 || enParcours == 4){
								offset = 9;
								enParcours = 2;
								delay = 0;
								printf("A* Manhattan\n");
								labyrinthe->entree = labyrinthe->sortie;
								labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								while(labyrinthe->sortie == labyrinthe->entree){
									labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = a_etoile(labyrinthe, labyrinthe->entree, distManhattan,
								                        labyrinthe->sortie, labyrinthe->colonnes, parentDest, &posPile);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
								defiler(fileParcours);

							}
							break;
						case SDLK_e:
							if(enParcours == 0 || enParcours == 4){
								offset = 6;
								enParcours = 2;
								delay = 0;
								printf("A* Tcheby\n");
								labyrinthe->entree = labyrinthe->sortie;
								labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								while(labyrinthe->sortie == labyrinthe->entree){
									labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = a_etoile(labyrinthe, labyrinthe->entree, distTchebytchev,
								                        labyrinthe->sortie, labyrinthe->colonnes, parentDest, &posPile);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
								defiler(fileParcours);

							}
							break;
						case SDLK_p:
							if(enParcours == 0 || enParcours == 4){
								offset = 12;
								delay = 0;
								enParcours = 3;
								direction = 5;
								printf("Dfs\n");
								labyrinthe->entree = labyrinthe->sortie;
								labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								while(labyrinthe->sortie == labyrinthe->entree){
									labyrinthe->sortie = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = dfs(labyrinthe, labyrinthe->entree);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								defiler(fileParcours);
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
							}
							break;
						case SDLK_f:
							if(enParcours == 0 || enParcours == 4){
								offset = 0;
								enParcours = 1;
								delay = 0;
								printf("Dijkstra\n");
								if(labyrinthe->entree == -1){
									labyrinthe->entree = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = dijkstra(labyrinthe, labyrinthe->entree, labyrinthe->sortie, parentDest,
								                        &posPile);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
								defiler(fileParcours);

							}
							break;
						case SDLK_q:
							if(enParcours == 0 || enParcours == 4){
								offset = 3;
								enParcours = 2;
								delay = 0;
								printf("A* Euclidienne\n");
								if(labyrinthe->entree == -1){
									labyrinthe->entree = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = a_etoile(labyrinthe, labyrinthe->entree, distEuclidienne,
								                        labyrinthe->sortie, labyrinthe->colonnes, parentDest, &posPile);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
								defiler(fileParcours);


							}
							break;
						case SDLK_s:
							if(enParcours == 0 || enParcours == 4){
								offset = 9;
								enParcours = 2;
								delay = 0;
								printf("A* Manhattan\n");
								if(labyrinthe->entree == -1){
									labyrinthe->entree = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = a_etoile(labyrinthe, labyrinthe->entree, distManhattan,
								                        labyrinthe->sortie, labyrinthe->colonnes, parentDest, &posPile);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
								defiler(fileParcours);

							}
							break;
						case SDLK_d:
							if(enParcours == 0 || enParcours == 4){
								offset = 6;
								enParcours = 2;
								delay = 0;
								printf("A* Tcheby\n");
								if(labyrinthe->entree == -1){
									labyrinthe->entree = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = a_etoile(labyrinthe, labyrinthe->entree, distTchebytchev,
								                        labyrinthe->sortie, labyrinthe->colonnes, parentDest, &posPile);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
								defiler(fileParcours);

							}
							break;
						case SDLK_m:
							if(enParcours == 0 || enParcours == 4){
								offset = 12;
								delay = 0;
								enParcours = 3;
								direction = 5;
								printf("Dfs\n");
								if(labyrinthe->entree == -1){
									labyrinthe->entree = choisirNoeud(labyrinthe->graphe->nbNoeuds);
								}
								reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
								fileParcours = dfs(labyrinthe, labyrinthe->entree);
								cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
								defiler(fileParcours);
								ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
								ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
							}
							break;
						default:
							break;
					}
					break;
				default:
					break;

			}
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}
	SDL_DestroyTexture(textureSol);
	SDL_DestroyTexture(textureMur);
	SDL_DestroyTexture(textureEntree);
	SDL_DestroyTexture(textureSortie);
	SDL_DestroyTexture(textureCarre);
	SDL_DestroyTexture(textureSolGris);
	endSdl(1, "Fermeture Normale", window, renderer);
	free(parentDest);
	libererLabyrinthe(labyrinthe);
}
