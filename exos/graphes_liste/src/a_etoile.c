#include "../headers/a_etoile.h"

float distEuclidienne(int x1, int x2, int y1, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float distTchebytchev(int x1, int x2, int y1, int y2) {
    return abs(x2 - x1) > abs(y2 - y1) ? abs(x2 - x1) : abs(y2 - y1);
}

float distManhattan(int x1, int x2, int y1, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

file_t *
a_etoile(labyrinthe_t *labyrinthe, noeud_t rac, float (*dist)(int, int, int, int), noeud_t dest, int dimLab,
         noeud_t *parentDest, int *pos) {

    file_t *file = creer_file();
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
        enfiler(file, noeudCourant);
        voisins = obtenirVoisins(labyrinthe, noeudCourant);
        for (i = 0; i < 4; i++) {
            voisinAct = voisins[i];
            if (voisinAct != -1 && d[voisinAct] == INT_MAX) {
                d[voisinAct] = d[noeudCourant] + 1 +
                               dist(voisinAct % dimLab,dest % dimLab,-voisinAct / dimLab, -dest / dimLab);
                parent[voisinAct] = noeudCourant;
                ajoutTasDijkstra(tas, voisinAct, d[voisinAct]);
            }
        }
        noeudCourant = suppressionRacineDijkstra(tas).som;
        free(voisins);
    }
    enfiler(file, dest);
    *pos = 0;
    noeudCourant = dest;
    while (noeudCourant != -1) {
        parentDest[*pos] = noeudCourant;
        noeudCourant = parent[noeudCourant];
        (*pos)++;
    }
    (*pos)--;
    libererTasDijkstra(tas);
    free(d);
    free(parent);
    return file;
}
