#include "../headers/dfs.h"

file_t * DFS(graph_t * graphe, int rac) {
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
    while (noeudCourant != -1) {
        enfiler(file, noeudCourant);
        int noeudTrouve = -1;
        int distAAjouter;
        int i = 0;
        while ((i < graphe->listeAretes->tailleCourante) && (noeudTrouve == -1)) {
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

        }
        else {
            noeudCourant = parent[noeudCourant];
        }
    }
    free(d);
    free(parent);
    return file;
}
