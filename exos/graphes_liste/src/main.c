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
#include "../headers/wifi.h"
#include <time.h>

#define LIGNE 4
#define COLONNE 4
#define SEED 1624441433
//#define SEED time(NULL)

int main() {
    int tailleCellW, tailleCellH, enParcours = 0, delay, pasW, pasH, max_delay = 5, posPile;
    cellule_t *cellCourante;
    noeud_t *parentDest;
    file_t *fileParcours;
    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textureMur, *textureSol, *textureSortie, *textureEntree;
    SDL_Point ptDep, ptArr, save;
    int window_w, window_h;
    tailleCellH = (WINDOW_H / (LIGNE * 2 + 1));
    tailleCellW = (WINDOW_W / (COLONNE * 2 + 1));
    window_w = (tailleCellW) * (COLONNE * 2 + 1);
    window_h = (tailleCellH) * (LIGNE * 2 + 1);
    printf("%d - %d\n", window_w, window_h);
    srand(SEED);
    labyrinthe_t *labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE, tailleCellW, tailleCellH, 0.05);
	//printf("%d\n", trouverCentre(labyrinthe->graphe));
	limitedDFS(labyrinthe,labyrinthe->entree,3);
    parentDest = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    initGraphics();
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(10, 10, window_w, window_h);
    renderer = createRenderer(window);
    textureMur = IMG_LoadTexture(renderer, "data/wall.png");
    textureSol = IMG_LoadTexture(renderer, "data/ground.png");
    textureEntree = IMG_LoadTexture(renderer, "data/entree.png");
    textureSortie = IMG_LoadTexture(renderer, "data/sortie.png");
    printf("GRAINE DE GENERATION DE LA FONCTION ALEATOIRE : %ld\n", SEED);
    SDL_bool program_on = SDL_TRUE;
    pasW = tailleCellW / max_delay * 2;
    pasH = tailleCellH / max_delay * 2;
    while (program_on) {
        SDL_Event event;
        SDL_RenderClear(renderer);
        drawLabyrinthe(renderer, labyrinthe, window_w, window_h, textureMur,
                       textureSol, textureEntree, textureSortie);
        if (enParcours && enParcours != 5) {
            if (file_est_vide(fileParcours)) {
                if (enParcours != 3 && (enParcours != 4)) {
                    enParcours = 5;
                    printf("Pile Position : %d\n", posPile);
                    cellCourante = labyrinthe->tableauCellules[parentDest[posPile]];
                    posPile--;
                    ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
                    ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
                    ptArr = ptDep;

                } else {
                    enParcours = 4;
                }
            } else {
                switch (enParcours) {
                    case 1:
                        if (delay == max_delay * 2) {
                            drawParcours(renderer, cellCourante, labyrinthe->tableauCellules,
                                         labyrinthe->colonnes);
                            cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
                            defiler(fileParcours);

                            delay = 0;
                        }
                        delay++;
                        break;
                    case 2:
                        if (delay == max_delay * 2) {
                            drawParcours(renderer, cellCourante, labyrinthe->tableauCellules,
                                         labyrinthe->colonnes);
                            cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
                            defiler(fileParcours);
                            delay = 0;
                        }
                        delay++;
                        break;
                    case 3:
                        if (delay == max_delay + 1) {
                            ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
                            ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
                            drawParcours(renderer, cellCourante, labyrinthe->tableauCellules,
                                         labyrinthe->colonnes);
                            cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
                            defiler(fileParcours);
                            ptArr.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
                            ptArr.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
                            delay = 0;
                        }
                        delay++;
                        drawMove(renderer, ptDep, tailleCellW, tailleCellH);
                        deplacement(&ptDep, &ptArr, pasW, pasH);
                        break;
                    default:
                        break;
                }
            }
        }
        if (enParcours == 4) {
            drawMove(renderer, ptArr, tailleCellW, tailleCellH);
        } else if (enParcours == 5) {

            if (delay == max_delay + 1 && posPile > -1) {
                ptDep.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
                ptDep.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
                drawParcours(renderer, cellCourante, labyrinthe->tableauCellules,
                             labyrinthe->colonnes);
                cellCourante = labyrinthe->tableauCellules[parentDest[posPile]];
                posPile--;
                ptArr.x = (cellCourante->j * cellCourante->w) * 2 + cellCourante->w;
                ptArr.y = (cellCourante->i * cellCourante->h) * 2 + cellCourante->h;
                delay = 0;
            }
            delay++;
            drawMove(renderer, ptDep, tailleCellW, tailleCellH);
            deplacement(&ptDep, &ptArr, pasW, pasH);
            if (posPile == -1) {
                enParcours = 4;
            }

        }
        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_d:
                            if (enParcours == 0 || enParcours == 4) {
                                enParcours = 1;
                                delay = 0;
                                printf("Dijkstra\n");
                                reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
                                fileParcours = dijkstra(labyrinthe, labyrinthe->entree, labyrinthe->sortie, parentDest,
                                                        &posPile);
                                cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
                                defiler(fileParcours);

                            }
                            break;
                        case SDLK_a:
                            if (enParcours == 0 || enParcours == 4) {
                                enParcours = 2;
                                delay = 0;
                                printf("A* Euclidienne\n");
                                reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
                                fileParcours = a_etoile(labyrinthe, labyrinthe->entree, distEuclidienne,
                                                        labyrinthe->sortie, labyrinthe->colonnes, parentDest, &posPile);
                                cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
                                defiler(fileParcours);


                            }
                            break;
                        case SDLK_z:
                            if (enParcours == 0 || enParcours == 4) {
                                enParcours = 2;
                                delay = 0;
                                printf("A* Manhattan\n");
                                reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
                                fileParcours = a_etoile(labyrinthe, labyrinthe->entree, distManhattan,
                                                        labyrinthe->sortie, labyrinthe->colonnes, parentDest, &posPile);
                                cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
                                defiler(fileParcours);

                            }
                            break;
                        case SDLK_e:
                            if (enParcours == 0 || enParcours == 4) {
                                enParcours = 2;
                                delay = 0;
                                printf("A* Tcheby\n");
                                reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
                                fileParcours = a_etoile(labyrinthe, labyrinthe->entree, distTchebytchev,
                                                        labyrinthe->sortie, labyrinthe->colonnes, parentDest, &posPile);
                                cellCourante = labyrinthe->tableauCellules[tete_file(fileParcours)];
                                defiler(fileParcours);

                            }
                            break;
                        case SDLK_p:
                            if (enParcours == 0 || enParcours == 4) {
                                delay = 0;
                                enParcours = 3;
                                printf("Dfs\n");
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
        SDL_Delay(2);
    }
    SDL_DestroyTexture(textureSol);
    SDL_DestroyTexture(textureMur);
    SDL_DestroyTexture(textureEntree);
    SDL_DestroyTexture(textureSortie);
    endSdl(1, "Fermeture Normale", window, renderer);
    generateGraphvizGraph(labyrinthe->graphe, "DEBUG");
    free(parentDest);
    libererLabyrinthe(labyrinthe);
}
