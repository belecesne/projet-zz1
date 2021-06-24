#include "../headers/wifi.h"

int trouverCentre(labyrinthe * labyrinthe, int alreadyCovered) {
    int * explored = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
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
    } while(!stop);
    return rac;
}

file_t * limited_DFS(graph_t * graphe, int rac, int limit) {
    file_t * file = creer_file();
    int * d = calloc(graphe->nbNoeuds, sizeof(int));
    int * parent = calloc(graphe->nbNoeuds, sizeof(int));
    for(int i = 0; i < graphe->nbNoeuds; i++) {
        if(i == rac) {
            d[i] = 0;
        }
        else {
            d[i] = INT_MAX;
        }
        parent[i] = -1;
    }
    int noeudCourant = rac;
    enfiler(file, rac);
    while (noeudCourant != -1) {
        int noeudTrouve = -1;
        int distAAjouter;
        int i = 0;
        while ((i < graphe->listeAretes->tailleCourante) && (noeudTrouve == -1) && (d[noeudCourant] < limit)) {
            if((graphe->listeAretes->array[i]->n1.valeur == noeudCourant) && (parent[graphe->listeAretes->array[i]->n2.valeur] == -1) && (graphe->listeAretes->array[i]->n2.valeur != rac)) {
                noeudTrouve = graphe->listeAretes->array[i]->n2.valeur;
                distAAjouter = graphe->listeAretes->array[i]->poids;
            }
            else if((graphe->listeAretes->array[i]->n2.valeur == noeudCourant) && (parent[graphe->listeAretes->array[i]->n1.valeur] == -1) && (graphe->listeAretes->array[i]->n1.valeur != rac)) {
                noeudTrouve = graphe->listeAretes->array[i]->n1.valeur;
                distAAjouter = graphe->listeAretes->array[i]->poids;
            }
            i++;
        }
        if(noeudTrouve != -1) {
            parent[noeudTrouve] = noeudCourant;
            d[noeudTrouve] = d[noeudCourant] + distAAjouter;
            noeudCourant = noeudTrouve;
            enfiler(file, noeudCourant);

        }
        else {
            noeudCourant = parent[noeudCourant];
        }
    }
    free(d);
    free(parent);
    return file;
}

file_t * posBornesWifi(labyrinthe_t * laby, int portee) {
    int * alreadyCovered = calloc(laby->graphe->nbNoeuds, sizeof(int));
    int nbNoeudsCouverts = laby->graphe->nbNoeuds;
}
