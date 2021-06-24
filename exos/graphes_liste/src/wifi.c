#include "../headers/wifi.h"

int trouverCentre(labyrinthe_t * labyrinthe, int alreadyCovered) {
    /*int * explored = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    int stop = 0;
    int rac = 0;
    do {
        int * d = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
        int * parent = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
        for(int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
            if(i == rac) {
                d[i] = 0;
            }
            else {
                d[i] = INT_MAX;
            }
            parent[i] = -1;
        }
        int noeudCourant = rac;
        while (noeudCourant != -1) {
            int noeudTrouve = -1;
            int distAAjouter;
            int i = 0;
            while ((i < labyrinthe->graphe->listeAretes->tailleCourante) && (noeudTrouve == -1) && (!alreadyCovered[noeudCourant])) {
                if((labyrinthe->graphe->listeAretes->array[i]->n1 == noeudCourant) && (!explored[labyrinthe->graphe->listeAretes->array[i]->n2]) && (parent[labyrinthe->graphe->listeAretes->array[i]->n2] == -1) && (labyrinthe->graphe->listeAretes->array[i]->n2 != rac)) {
                   noeudTrouve = labyrinthe->graphe->listeAretes->array[i]->n2;
                   distAAjouter = labyrinthe->graphe->listeAretes->array[i]->poids;
                }
                else if((labyrinthe->graphe->listeAretes->array[i]->n2 == noeudCourant) && (!explored[labyrinthe->graphe->listeAretes->array[i]->n1]) && (parent[labyrinthe->graphe->listeAretes->array[i]->n1] == -1) && (labyrinthe->graphe->listeAretes->array[i]->n1 != rac)) {
                    noeudTrouve = labyrinthe->graphe->listeAretes->array[i]->n1;
                    distAAjouter = labyrinthe->graphe->listeAretes->array[i]->poids;
                }
                i++;
            }
            if(noeudTrouve != -1) {
                parent[noeudTrouve] = noeudCourant;
                d[noeudTrouve] = d[noeudCourant] + distAAjouter;
                noeudCourant = noeudTrouve;
            }
            else {
                noeudCourant = parent[noeudCourant];
            }
        }
        int max = -1;
        int ind = -1;
        for(int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
            if(d[i] > max && d[i] != INT_MAX) {
                max = d[i];
                ind = i;
            }
        }
        if(max == 0) {
            stop = 1;
        }
        else {
            explored[ind] = 1;
        }
        rac = ind;
        free(d);
        free(parent);
    } while(!stop);*/
    return 0;
}

file_t * limitedDFS(labyrinthe_t * labyrinthe, int rac, int limit) {
    file_t *file = creer_file();
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
    noeud_t noeudCourant = rac;
    noeud_t *voisins;
    while (noeudCourant != -2) {
        enfiler(file, noeudCourant);
        voisins = obtenirVoisins(labyrinthe, noeudCourant);
        if (voisins[0] != -1 && parent[voisins[0]] == -1 && d[parent[voisins[0]] < limit]) {
            parent[voisins[0]] = noeudCourant;
            d[voisins[0]] = d[noeudCourant] + 1;
            noeudCourant = voisins[0];

        } else if (voisins[1] != -1 && parent[voisins[1]] == -1 && d[parent[voisins[1]] < limit]) {
            parent[voisins[1]] = noeudCourant;
            d[voisins[1]] = d[noeudCourant] + 1;
            noeudCourant = voisins[1];

        } else if (voisins[2] != -1 && parent[voisins[2]] == -1 && d[parent[voisins[2]] < limit]) {
            parent[voisins[2]] = noeudCourant;
            d[voisins[2]] = d[noeudCourant] + 1;
            noeudCourant = voisins[2];

        } else if (voisins[3] != -1 && parent[voisins[3]] == -1 && d[parent[voisins[3]] < limit]) {
            parent[voisins[3]] = noeudCourant;
            d[voisins[3]] = d[noeudCourant] + 1;
            noeudCourant = voisins[3];
        } else {
            noeudCourant = parent[noeudCourant];
        }

    }
    enfiler(file, rac);
    for(int i = 0; i < labyrinthe->graphe->nbNoeuds; i++){
        if(d[i]<= limit)
            printf("%d - %d\n",i,d[i]);
    }
    afficher_file(file);
    free(d);
    free(parent);
    return file;
}

file_t * posBornesWifi(labyrinthe_t * laby, int portee) {
    int * alreadyCovered = calloc(laby->graphe->nbNoeuds, sizeof(int));
    int nbNoeudsCouverts = laby->graphe->nbNoeuds;
}
