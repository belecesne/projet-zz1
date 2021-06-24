#include "../headers/dfs.h"


file_t *dfs(labyrinthe_t *labyrinthe, noeud_t rac) {
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
    noeud_t *voisins, voisinAct;
    while (noeudCourant != -2) {
        enfiler(file, noeudCourant);
        voisins = obtenirVoisins(labyrinthe, noeudCourant);
        if (voisins[0] != -1 && parent[voisins[0]] == -1) {
            parent[voisins[0]] = noeudCourant;
            d[voisins[0]] = d[noeudCourant] + 1;
            noeudCourant = voisins[0];

        } else if (voisins[1] != -1 && parent[voisins[1]] == -1) {
            parent[voisins[1]] = noeudCourant;
            d[voisins[1]] = d[noeudCourant] + 1;
            noeudCourant = voisins[1];

        } else if (voisins[2] != -1 && parent[voisins[2]] == -1) {
            parent[voisins[2]] = noeudCourant;
            d[voisins[2]] = d[noeudCourant] + 1;
            noeudCourant = voisins[2];

        } else if (voisins[3] != -1 && parent[voisins[3]] == -1) {
            parent[voisins[3]] = noeudCourant;
            d[voisins[3]] = d[noeudCourant] + 1;
            noeudCourant = voisins[3];
        } else {
            noeudCourant = parent[noeudCourant];
        }

    }

    enfiler(file, rac);
    free(d);
    free(parent);
    return file;
}
/*
file_t *dfs(labyrinthe_t *labyrinthe, noeud_t rac) {
    file_t *file = creer_file();
    int *d = calloc(labyrinthe->graphe->nbNoeuds, sizeof(int));
    noeud_t *parent = calloc(labyrinthe->graphe->nbNoeuds, sizeof(noeud_t));
    for (int i = 0; i < labyrinthe->graphe->nbNoeuds; i++) {
        if (i == rac) {
            d[i] = 0;
        } else {
            d[i] = INT_MAX;
        }
        parent[i] = -1;
    }
    noeud_t noeudTrouve = -1;
    noeud_t *voisins, voisinAct;
    int distAAjouter, i, enfile = 0;
    noeud_t noeudCourant = rac;
    enfiler(file, noeudCourant);
    i = 0;
    while (noeudCourant != -1) {
        voisins = obtenirVoisins(labyrinthe, noeudCourant);
        while (i < 4 && voisins[i] == -1) {
            i++;
        }
        voisinAct = voisins[i];
        if (voisinAct != -1 && d[voisinAct] == INT_MAX) {
            enfile = 1;
            d[voisinAct] = d[noeudCourant] + 1;
            parent[voisinAct] = noeudCourant;
        } else {
            noeudCourant = parent[noeudCourant];
        }
        if (i == 4) {
            i = 0;
        }
        if (enfile) {
            enfiler(file, voisinAct);
            enfile = 0;
        }
    }
    enfiler(file, rac);
    afficher_file(file);
    free(d);
    free(parent);
    return file;
}*/