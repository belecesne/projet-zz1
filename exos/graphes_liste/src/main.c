#include "../headers/graph.h"
#include "../headers/maillon_arete.h"
#include <time.h>

int main() {
    srand(time(NULL));
    graph_t *graphe = nouveau_graphe(12);
    noeud_t *tabNode[12];
    int j, k;
    for (int i = 0; i < 12; i++) {
        tabNode[i] = creerNoeud(i);
    }
    k = 1, j = 3;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 1, j = 0;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 1, j = 2;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 0, j = 2;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 4, j = 5;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 8, j = 7;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 9, j = 7;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 11, j = 7;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 10, j = 7;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));
    k = 8, j = 9;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 8, j = 11;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 9, j = 11;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));

    k = 9, j = 10;
    insertionArrete(graphe, creerArete(tabNode[k], tabNode[j],1));




    generateGraphvizGraph(graphe, "graph");
    generateConnectedComponents(graphe, "cc");
    for(int i = 0; i < 12; free(tabNode[i++]));
    liberer_graphe(graphe);
}