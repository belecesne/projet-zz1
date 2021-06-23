#include "../headers/dijkstra.h"


file_t *dijkstra(labyrinthe_t *labyrinthe, noeud_t rac, noeud_t dest, noeud_t * parentDest, int *pos) {
    file_t *file = creer_file();
    int *d = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    noeud_t * parent = calloc(labyrinthe->graphe->nbNoeuds, sizeof(noeud_t));
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
                d[voisinAct] = d[noeudCourant] + 1;
                parent[voisinAct] = noeudCourant;
                ajoutTasDijkstra(tas, voisinAct, d[voisinAct]);
            }
        }
        noeudCourant = suppressionRacineDijkstra(tas).som;
        free(voisins);
    }
    noeudCourant = dest;
    *pos = 0;
    while(noeudCourant != -1 ){
        parentDest[*pos] = noeudCourant;
        noeudCourant = parent[noeudCourant];
        (*pos)++;
    }
    (*pos)--;
    enfiler(file, dest);
    libererTasDijkstra(tas);
    free(d);
    free(parent);
    return file;
}
