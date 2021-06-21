#include "../headers/graph.h"
#include "../headers/maillon_arete.h"
#include <time.h>
int main() {
    srand(time(NULL));
    graph_t *graphe = nouveau_graphe(12);
    int j, k;
    noeud_t nk, nj;

    k = 1, j = 3;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 1, j = 0;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 1, j = 2;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 0, j = 2;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 4, j = 5;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 8, j = 7;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 9, j = 7;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 11, j = 7;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 10, j = 7;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 8, j = 9;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 8, j = 11;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 9, j = 11;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));

    k = 9, j = 10;
    nk.valeur = k;
    nj.valeur = j;
    insertionArrete(graphe, creerArete(nk, nj,1));




    generateGraphvizGraph(graphe, "graph");
    generateConnectedComponents(graphe, "cc");
    graph_t * arbre = kruskal(graphe);
    generateGraphvizGraph(arbre, "arbre");

    liberer_graphe(graphe);
}
