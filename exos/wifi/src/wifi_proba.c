#include "../headers/wifi_proba.h"

int longueurPlusCourtChemin(labyrinthe_t *labyrinthe, noeud_t rac, noeud_t dest) {
    int *d = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    noeud_t *parent = calloc(labyrinthe->graphe->nbNoeuds, sizeof(noeud_t));
    tas_dijkstra_t *tas = creerTasDijktra();
    noeud_t *voisins, voisinAct, noeudCourant;
    int i;
    for (i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        if (i == rac) {
            d[i] = 0;
        } else {
            d[i] = INT_MAX;
        }
        parent[i] = -1;
    }
    noeudCourant = rac;
    while (noeudCourant != dest) {
        voisins = obtenirVoisins(labyrinthe, noeudCourant);
        for (i = 0; i < 4; i++) {
            voisinAct = voisins[i];
            if (voisinAct != -1 && d[voisinAct] == INT_MAX) {
                d[voisinAct] = d[noeudCourant] + 1;
                parent[voisinAct] = noeudCourant;
                ajoutTasDijkstra(tas, voisinAct, d[voisinAct]);
            }
        }
        noeudCourant = suppressionRacineDijkstra(tas).som;
        free(voisins);
    }
    noeudCourant = dest;
    int max;
    max = -1;
    for (int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        if (d[i] > max && d[i] != INT_MAX) {
            max = d[i];
        }
    }
    libererTasDijkstra(tas);
    free(d);
    free(parent);
    return max;
}

int distancePlusLoin(labyrinthe_t *labyrinthe, noeud_t rac, noeud_t *dest) {
    int *d = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    noeud_t *parent = calloc(labyrinthe->graphe->nbNoeuds, sizeof(noeud_t));
    tas_dijkstra_t *tas = creerTasDijktra();
    noeud_t *voisins, voisinAct, noeudCourant;
    int i;
    for (i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        if (i == rac) {
            d[i] = 0;
        } else {
            d[i] = INT_MAX;
        }
        parent[i] = -1;
    }
    int j;
    j = 1;
    noeudCourant = rac;
    while (j == 1 || !tasVideDijkstra(tas)) {
        j = 0;
        voisins = obtenirVoisins(labyrinthe, noeudCourant);
        for (i = 0; i < 4; i++) {
            voisinAct = voisins[i];
            if (voisinAct != -1 && d[voisinAct] == INT_MAX) {
                d[voisinAct] = d[noeudCourant] + 1;
                parent[voisinAct] = noeudCourant;
                ajoutTasDijkstra(tas, voisinAct, d[voisinAct]);
            }
        }
        noeudCourant = suppressionRacineDijkstra(tas).som;
        free(voisins);
    }
    int max, ind;
    max = -1;
    ind = -1;
    for (int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        if (d[i] > max && d[i] != INT_MAX) {
            max = d[i];
            ind = i;
        }
    }
    libererTasDijkstra(tas);
    free(d);
    free(parent);
    *dest = ind;
    return max;
}

cellule_t *proposition(labyrinthe_t *labyrinthe, noeud_t borne) {
    int rand_dep;
    rand_dep = rand() % 4;
    noeud_t *voisins, voisin;
    voisins = obtenirVoisins(labyrinthe, borne);
    while (voisins[rand_dep] == -1 || labyrinthe->tableauCellules[voisins[rand_dep]]->noeud == -1) {
        rand_dep = rand() % 4;
    }
    voisin = voisins[rand_dep];
    free(voisins);
    return labyrinthe->tableauCellules[voisin];
}

double calculProba(int D1, int D2, double T) {
    int deltaE = D1 - D2;
    double x = ((rand() % 891975) / 891975.0);
    double proba = 1;
    if (deltaE < 0) {
        proba = exp((deltaE * 1.0) / T);
    }
    //printf("La proba est : %lf avec x = %lf\n",proba,x);
    return proba > x;
}

file_t * recuitSimule(labyrinthe_t *labyrinthe, noeud_t *bornes, int nbBornes, double erreur) {
    file_t * file;
    file = creer_file();
    int i = 0, compteur = 0, comptFixe = 0;
    int max = -1;
    double T;
    noeud_t *noeudsLoins, noeudLoin, borneChoisie;
    cellule_t *cell;
    int *distance_loin, D1, D2, x;
    noeudsLoins = malloc(sizeof(noeud_t) * nbBornes);
    distance_loin = malloc(sizeof(int) * nbBornes);

    T = MAX(labyrinthe->lignes, labyrinthe->colonnes);
    while (T > erreur) {
        comptFixe++;
        max = -1;
        //printf("------------------------------\n");
        //printf("DEBUT\n");
        for (i = 0; i < nbBornes; i++) {
            distance_loin[i] = distancePlusLoin(labyrinthe, bornes[i], &(noeudsLoins[i]));
            //printf("Distance Max %d - %d\n",bornes[i], noeudsLoins[i]);
            if (distance_loin[i] > max) {
                max = distance_loin[i];
                noeudLoin = noeudsLoins[i];
            }
        }
        borneChoisie = rand() % nbBornes;
        //printf("Borne choisie n??%d d'emplacement %d ??loign??e de %d\n",borneChoisie, bornes[borneChoisie], noeudLoin);
        D1 = longueurPlusCourtChemin(labyrinthe, bornes[borneChoisie], noeudLoin);
        //printf("D1 : %d\n",D1);
        cell = proposition(labyrinthe, bornes[borneChoisie]);
        //printf("Valeur de la proposition : %d\n",cell->noeud);
        D2 = longueurPlusCourtChemin(labyrinthe, cell->noeud, noeudLoin);
        //printf("D2 : %d\n",D2);
        if ((x = calculProba(D1, D2, T))) {
            i = 0;
            int bool = 1;
            while(i < nbBornes && bool){
                if(bornes[i] == cell->noeud ){
                    bool = !bool;
                }
                i++;
            }
            if(bool){
                bornes[borneChoisie] = cell->noeud;

                enfiler(file,borneChoisie);
                enfiler(file,cell->noeud);
            }
            //printf("Calcul des probas : Accepete ? : %d!\n",x);
            //printf("Emplacement de la nouvelle borne : %d\n",bornes[borneChoisie]);

        }

        if (compteur == COMPTEUR) {
            // printf("La valeur de la temp??rature est : %lf\n",T);
            T = T * COEFF;
            compteur = 0;
        }
        compteur++;
    }
    max = -1;
    for (i = 0; i < nbBornes; i++) {
        distance_loin[i] = distancePlusLoin(labyrinthe, bornes[i], &(noeudsLoins[i]));
        printf("Distance Max %d - %d\n",bornes[i], noeudsLoins[i]);
        if (distance_loin[i] > max) {
            max = distance_loin[i];
            noeudLoin = noeudsLoins[i];
        }
    }
    printf("%d\n",max);
    for (int i = 0; i < nbBornes; i++) {
        printf("Borne %d : %d\n", i, bornes[i]);
    }
    free(noeudsLoins);
    free(distance_loin);
    return file;
}

void colorierPortee(labyrinthe_t * laby, noeud_t * bornes, int nbBornes, SDL_Renderer * renderer) {
    int i = nbBornes;
    file_t * file = creer_file();
    for(int k = 0; k < nbBornes; k++) {
        enfiler(file, bornes[k]);
        laby->tableauCellules[bornes[k]]->etat = 1;
    }
    int stopEnfiler = 0;
    while (!file_est_vide(file)) {
        noeud_t noeudCourant = tete_file(file);
        defiler(file);
        noeud_t * voisins = obtenirVoisins(laby, noeudCourant);
        for(int j = 0; j < 4; j++) {
            if((voisins[j] != -1) && (laby->tableauCellules[voisins[j]]->noeud != 1) && (!stopEnfiler)) {
                enfiler(file, voisins[j]);
                i++;
            }
        }
        colorierVoisins(renderer, laby->tableauCellules[noeudCourant], laby->tableauCellules, laby->colonnes);
        if(i >= laby->graphe->nbNoeuds) {
            stopEnfiler = 1;
        }
    }
    liberer_file(file);
}
