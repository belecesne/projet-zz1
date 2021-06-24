#include "../headers/wifi.h"

int trouverCentre(labyrinthe_t *labyrinthe, int caserecouverte) {
    file_t *file = creer_file();
    int *d = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    noeud_t *parent = calloc(labyrinthe->graphe->nbNoeuds, sizeof(noeud_t));
    noeud_t *explored = calloc(labyrinthe->graphe->nbNoeuds, sizeof(noeud_t));
    int rac = 0, max, ind;
    while (labyrinthe->tableauCellules[rac]->etat == 11) {
        rac = rand() % labyrinthe->graphe->nbNoeuds;
    }

    for (int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        if (i == rac) {
            d[i] = 0;
            parent[i] = -2;
        } else {
            d[i] = INT_MAX;
            parent[i] = -1;
        }
        explored[i] = 0;
    }
    noeud_t noeudCourant = rac;
    noeud_t *voisins;
    int caseGrise = 0;
    while (caseGrise != labyrinthe->graphe->nbNoeuds - caserecouverte) {
        noeudCourant = rac;
        while (noeudCourant != -2) {
            voisins = obtenirVoisins(labyrinthe, noeudCourant);
            if (voisins[0] != -1 && parent[voisins[0]] == -1 && !explored[voisins[0]]) {
                parent[voisins[0]] = noeudCourant;
                d[voisins[0]] = d[noeudCourant] + 1;
                /*if(labyrinthe->tableauCellules[voisins[0]]->etat != 11){
                    d[voisins[0]]++;
                }*/
                noeudCourant = voisins[0];

            } else if (voisins[1] != -1 && parent[voisins[1]] == -1 && !explored[voisins[1]]) {
                parent[voisins[1]] = noeudCourant;
                d[voisins[1]] = d[noeudCourant] + 1;
                /*if(labyrinthe->tableauCellules[voisins[1]]->etat != 11){
                    d[voisins[1]]++;
                }*/
                noeudCourant = voisins[1];

            } else if (voisins[2] != -1 && parent[voisins[2]] == -1 && !explored[voisins[2]]) {
                parent[voisins[2]] = noeudCourant;
                d[voisins[2]] = d[noeudCourant] + 1;
                /*if(labyrinthe->tableauCellules[voisins[2]]->etat != 11){
                    d[voisins[2]]++;
                }*/
                noeudCourant = voisins[2];

            } else if (voisins[3] != -1 && parent[voisins[3]] == -1 && !explored[voisins[3]]) {
                parent[voisins[3]] = noeudCourant;
                d[voisins[3]] = d[noeudCourant] + 1;
                /*if(labyrinthe->tableauCellules[voisins[3]]->etat != 11){
                    d[voisins[3]]++;
                }*/
                noeudCourant = voisins[3];
            } else {
                noeudCourant = parent[noeudCourant];
            }
        }
        max = -1;
        ind = -1;
        for (int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
            if (d[i] > max && d[i] != INT_MAX && labyrinthe->tableauCellules[i]->etat != 11) {
                max = d[i];
                ind = i;
            }
        }
        explored[ind] = 1;
        caseGrise++;
        rac = ind;
        for (int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
            if (i == rac) {
                d[i] = 0;
                parent[i] = -2;
            } else {
                d[i] = INT_MAX;
                parent[i] = -1;
            }
        }
    }
    liberer_file(file);
    for (int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        printf("Distance de la racine %d : %d : %d\n", rac, i, d[i]);
    }
    free(parent);
    free(explored);
    free(d);
    return rac;
}


int limitedDFS(labyrinthe_t *labyrinthe, int rac, int limit, int *caseGrise) {
    int *d = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    noeud_t *parent = calloc(labyrinthe->graphe->nbNoeuds, sizeof(noeud_t));
    for (int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        if (i == rac) {
            d[i] = 0;
            parent[i] = -2;
        } else {
            d[i] = INT_MAX;
            parent[i] = -1;
        }
    }
    if (labyrinthe->tableauCellules[rac]->etat != 11) {
        (*caseGrise)++;
    }
    noeud_t noeudCourant = rac;
    noeud_t *voisins;
    while (noeudCourant != -2) {
        labyrinthe->tableauCellules[noeudCourant]->etat = 11;
        voisins = obtenirVoisins(labyrinthe, noeudCourant);
        if (voisins[0] != -1 && parent[voisins[0]] == -1 && d[noeudCourant] < limit) {
            parent[voisins[0]] = noeudCourant;
            d[voisins[0]] = d[noeudCourant] + 1;
            noeudCourant = voisins[0];
            (*caseGrise)++;

        } else if (voisins[1] != -1 && parent[voisins[1]] == -1 && d[noeudCourant] < limit) {
            parent[voisins[1]] = noeudCourant;
            d[voisins[1]] = d[noeudCourant] + 1;
            noeudCourant = voisins[1];
            (*caseGrise)++;

        } else if (voisins[2] != -1 && parent[voisins[2]] == -1 && d[noeudCourant] < limit) {
            parent[voisins[2]] = noeudCourant;
            d[voisins[2]] = d[noeudCourant] + 1;
            noeudCourant = voisins[2];
            (*caseGrise)++;


        } else if (voisins[3] != -1 && parent[voisins[3]] == -1 && d[noeudCourant] < limit) {
            parent[voisins[3]] = noeudCourant;
            d[voisins[3]] = d[noeudCourant] + 1;
            noeudCourant = voisins[3];
            (*caseGrise)++;

        } else {
            noeudCourant = parent[noeudCourant];
        }
    }
    printf("Racine : %d\n", rac);
    for (int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        printf("%d - %d\n", i, d[i]);
    }
    printf("Cases recouvertes : %d\n", *caseGrise);
    free(d);
    free(parent);
    return 0;
}

file_t *posBornesWifi(labyrinthe_t *labyrinte, int portee) {
    int casesBlanches = labyrinte->graphe->nbNoeuds;
    file_t *file = creer_file();
    int centre, i = 0;
    int caserecouverte = 0;
    printf("Portee : %d\n", portee);
    while (caserecouverte < labyrinte->graphe->nbNoeuds) {
        printf("##################\n");
        centre = trouverCentre(labyrinte, caserecouverte);
        printf("Centre trouvée en %d\n", centre);
        limitedDFS(labyrinte, centre, portee, &caserecouverte);
        printf("Nombre de cases recouvertes : %d\n", caserecouverte);
        printf("--------------------\n\n");
        enfiler(file, centre);
    }
    afficher_file(file);
    return file;
}

