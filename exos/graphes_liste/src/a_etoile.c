#include "../headers/a_etoile.h"

float distEuclidienne(int x1, int x2, int y1, int y2) {
    return sqrt((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1));
}

float distTchebytchev(int x1, int x2, int y1, int y2) {
    return abs(x2-x1) > abs(y2-y1) ? abs(x2-x1) : abs(y2-y1);
}

float distManhattan(int x1, int x2, int y1, int y2) {
    return abs(x2-x1) + abs(y2-y1);
}

file_t * a_etoile(graph_t * graphe, int rac, float (*dist)(int, int, int, int), int noeudDest, int dimLab) {
    file_t * file = creer_file();
    int * d = calloc(graphe->nbNoeuds, sizeof(int));
    int * parent = calloc(graphe->nbNoeuds, sizeof(int));
    tas_dijkstra_t * tas = creerTasDijktra();
    for(int i = 0; i < graphe->nbNoeuds; i++) {
        if(i == rac) {
            d[i] = 0;
        }
        else {
            d[i] = INT_MAX;
        }
        parent[i] = -1;
        elem_tas_dijkstra_t e = {i, d[i]};
        ajoutTasDijkstra(tas, e);
    }
    elem_tas_dijkstra_t e = suppressionRacineDijkstra(tas);
    while(!tasVideDijkstra(tas) && (e.som != noeudDest)) {
        enfiler(file, e.som);
        for(int i = 0; i < graphe->listeAretes->tailleCourante; i++) {
            if((graphe->listeAretes->array[i]->n1.valeur == e.som) && (d[graphe->listeAretes->array[i]->n2.valeur] > d[e.som] + graphe->listeAretes->array[i]->poids)) {
                d[graphe->listeAretes->array[i]->n2.valeur] = d[e.som] + graphe->listeAretes->array[i]->poids;
                parent[graphe->listeAretes->array[i]->n2.valeur] = e.som;
                modifValeurTasDijkstra(tas, graphe->listeAretes->array[i]->n2.valeur, d[e.som] + graphe->listeAretes->array[i]->poids + dist((graphe->listeAretes->array[i]->n2.valeur)/dimLab, noeudDest/dimLab, (graphe->listeAretes->array[i]->n2.valeur)%dimLab, noeudDest%dimLab));
            }
            else if((graphe->listeAretes->array[i]->n2.valeur == e.som) && (d[graphe->listeAretes->array[i]->n1.valeur] > d[e.som] + graphe->listeAretes->array[i]->poids)) {
                d[graphe->listeAretes->array[i]->n1.valeur] = d[e.som] + graphe->listeAretes->array[i]->poids;
                parent[graphe->listeAretes->array[i]->n1.valeur] = e.som;
                modifValeurTasDijkstra(tas, graphe->listeAretes->array[i]->n1.valeur, d[e.som] + graphe->listeAretes->array[i]->poids + dist((graphe->listeAretes->array[i]->n1.valeur)/dimLab, noeudDest/dimLab, (graphe->listeAretes->array[i]->n1.valeur)%dimLab, noeudDest%dimLab));
            }
        }
        e = suppressionRacineDijkstra(tas);
    }
    enfiler(file, noeudDest);
    libererTasDijkstra(tas);
    free(d);
    free(parent);
    return file;
}
