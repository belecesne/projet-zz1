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
#include "../headers/wifi_proba.h"
#include <time.h>

#define LIGNE 10
#define COLONNE 10
#define SEED time(NULL)//1624555474//time(NULL)//1624554986//1624441433
#define PROBA 0.7
#define N_BORNES 4
//#define SEED time(NULL)

int main() {
    int tailleCellW, tailleCellH, delay, max_delay = 5, affichageAntenne = 0, dejaDeplace, borneChoisie, parcouru = 0, casesRecouvertes = 0, portee = 0;
    cellule_t *cell;
    noeud_t *parentDest;
    file_t *fileParcours, *fileAntenne, *fileCourante, *fileFuture, *fileTemp;
    fileCourante = creer_file();
    fileFuture = creer_file();
    fileParcours = NULL;
    fileAntenne = NULL;
    SDL_DisplayMode disp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textureMur, *textureSol, *textureSortie, *textureEntree, *textureAntenne, *textureSolGris;
    SDL_Point pointAntenne;
    long int seed = SEED;
    int window_w, window_h, offset, t;
    tailleCellH = (WINDOW_H / (LIGNE * 2 + 1));
    tailleCellW = (WINDOW_W / (COLONNE * 2 + 1));
    window_w = (tailleCellW) * (COLONNE * 2 + 1);
    window_h = (tailleCellH) * (LIGNE * 2 + 1);
    SDL_Rect posScore = {window_w - 200, 0, window_w - 10, tailleCellH};
    printf("%d - %d\n", window_w, window_h);
    srand(seed);
    labyrinthe_t *labyrinthe = creerLabyrintheQqc(LIGNE, COLONNE, tailleCellW, tailleCellH, PROBA);
    //printf("Centre trouvé en %d\n", trouverCentre(labyrinthe));
    //limitedDFS(labyrinthe,labyrinthe->entree,3);
    //posBornesWifi(labyrinthe,2);
    noeud_t bornes[N_BORNES], *voisins;
    for (int i = 0; i < N_BORNES; i++) {
        bornes[i] = -1;
    }
    printf("GRAINE DE GENERATION DE LA FONCTION ALEATOIRE : %ld\n", seed);
    parentDest = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    initGraphics();
    const char *titles[] = {"Dijkstra .", "Dijkstra . .", "Dijkstra . . .", "A* Euclidienne .", "A* Euclidienne . .",
                            "A* Euclidienne . . .", "A* Tchebychev .", "A* Tchebychev . .", "A* Tchebychev . . .",
                            "A* Manhattan .", "A* Manhattan . .", "A* Manhattan . . .", "DFS .", "DFS . .", "DFS . . .",
                            "WIFI", "WIFI", "WIFI", "Extension du WIFI en cours .",
                            "Extension du WIFI en cours . .", "Extension du WIFI en cours . . ."
    };
    char porteeStr[50];


    offset = 15;
    SDL_GetCurrentDisplayMode(0, &disp);
    window = createWindow(10, 10, window_w, window_h);
    renderer = createRenderer(window);
    textureMur = IMG_LoadTexture(renderer, "data/wall.png");
    textureSolGris = IMG_LoadTexture(renderer, "data/groundGrey.png");
    textureSol = IMG_LoadTexture(renderer, "data/ground.png");
    textureEntree = IMG_LoadTexture(renderer, "data/entree.png");
    textureSortie = IMG_LoadTexture(renderer, "data/sortie.png");
    textureAntenne = IMG_LoadTexture(renderer, "data/antenne.png");

    if (TTF_Init() < 0) {
        endSdl(0, "Erreur dans l'init de TTF", window, renderer);
    }
    TTF_Font *font = NULL;
    font = TTF_OpenFont("./data/Simvoni.ttf", 25);
    if (font == NULL) {
        endSdl(0, "Erreur dans l'ouverture de la police", window, renderer);
    }
    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface *textSurface = NULL;
    SDL_Texture *textTexture = NULL;
    SDL_bool program_on = SDL_TRUE;

    while (program_on) {
        SDL_Event event;
        SDL_RenderClear(renderer);

        if (delay == max_delay) {
            SDL_SetWindowTitle(window, titles[offset + (++t % 3)]);
        }
        drawLabyrinthe(renderer, labyrinthe, window_w, window_h, textureMur,
                       textureSol, textureEntree, textureSortie, textureSolGris, !affichageAntenne);
        if (affichageAntenne && !file_est_vide(fileAntenne)) {
            dejaDeplace = 0;
            parcouru = 1;
            for (int i = 0; i < N_BORNES; i++) {
                borneChoisie = tete_file(fileAntenne);
                if (borneChoisie == i && !dejaDeplace) {
                    dejaDeplace = 1;
                    defiler(fileAntenne);
                    bornes[borneChoisie] = tete_file(fileAntenne);
                    cell = labyrinthe->tableauCellules[bornes[borneChoisie]];
                    //printf("Borne %d deplacé en %d\n", borneChoisie, cell->noeud);
                    defiler(fileAntenne);
                    pointAntenne.x = (cell->j * cell->w) * 2 + cell->w;
                    pointAntenne.y = (cell->i * cell->h) * 2 + cell->h;
                    drawText(renderer, pointAntenne, tailleCellW, tailleCellH, textureAntenne);
                } else {
                    //printf("Non déplacement de la borne %d\n",i);
                    cell = labyrinthe->tableauCellules[bornes[i]];
                    pointAntenne.x = (cell->j * cell->w) * 2 + cell->w;
                    pointAntenne.y = (cell->i * cell->h) * 2 + cell->h;
                    drawText(renderer, pointAntenne, tailleCellW, tailleCellH, textureAntenne);
                }
            }
            for (int i = 0; i < N_BORNES; i++) {
                if (file_est_vide(fileAntenne)) {
                    enfiler(fileCourante, bornes[i]);
                }
            }
        } else if (bornes[0] != -1) {
            for (int i = 0; i < N_BORNES; i++) {
                cell = labyrinthe->tableauCellules[bornes[i]];
                pointAntenne.x = (cell->j * cell->w) * 2 + cell->w;
                pointAntenne.y = (cell->i * cell->h) * 2 + cell->h;
                drawText(renderer, pointAntenne, tailleCellW, tailleCellH, textureAntenne);
            }
            if (parcouru && casesRecouvertes < labyrinthe->graphe->nbNoeuds && delay == max_delay * 2) {
                delay = 0;
                while (!file_est_vide(fileCourante)) {
                    borneChoisie = tete_file(fileCourante);
                    defiler(fileCourante);
                    cell = labyrinthe->tableauCellules[borneChoisie];
                    if (cell->etat == 0) {
                        casesRecouvertes++;
                        cell->etat = 2;
                    }
                    voisins = obtenirVoisins(labyrinthe, borneChoisie);
                    labyrinthe->tableauCellules[borneChoisie]->etat = 2;
                    for (int i = 0; i < 4; i++) {
                        if (voisins[i] != -1 && labyrinthe->tableauCellules[voisins[i]]->etat == 0) {
                            casesRecouvertes++;
                            labyrinthe->tableauCellules[voisins[i]]->etat = 2;
                            enfiler(fileFuture, voisins[i]);
                        }
                    }
                }
                portee++;
                printf("La portée actuelle du wifi est : %d\n", portee);
                fileTemp = fileCourante;
                fileCourante = fileFuture;
                fileFuture = fileTemp;
            }
            delay++;
        }
        if (portee != 0) {
            sprintf(porteeStr, "Portee actuelle : %d", portee);
            textSurface = TTF_RenderText_Blended(font, porteeStr, color);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture == NULL) {
                endSdl(0, "Impossible de créer la surface", window, renderer);
            }
            SDL_QueryTexture(textTexture, NULL, NULL, &posScore.w, &posScore.h);
            SDL_RenderCopy(renderer, textTexture, NULL, &posScore);
        }
        if(casesRecouvertes >= labyrinthe->graphe->nbNoeuds){
            offset = 15;
        }
        while (program_on && SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    program_on = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_r:
                            offset = 18;
                            liberer_file(fileAntenne);
                            reinitEtat(labyrinthe->tableauCellules, labyrinthe->graphe->nbNoeuds);
                            for (int i = 0; i < N_BORNES; i++) {
                                bornes[i] = rand() % labyrinthe->graphe->nbNoeuds;
                            }
                            fileAntenne = recuitSimule(labyrinthe, bornes, N_BORNES, 4.9);
                            printf("Longueur de la file : %d \n", fileAntenne->nb_elements / 2);
                            affichageAntenne = 1;
                            delay = 0;
                            casesRecouvertes = 0;
                            portee = 0;

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
    SDL_DestroyTexture(textureAntenne);
    SDL_DestroyTexture(textureSolGris);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    endSdl(1, "Fermeture Normale", window, renderer);
    free(parentDest);
    liberer_file(fileAntenne);
    liberer_file(fileParcours);
    liberer_file(fileCourante);
    liberer_file(fileFuture);
    libererLabyrinthe(labyrinthe);
}
