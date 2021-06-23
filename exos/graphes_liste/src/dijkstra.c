#include "../headers/dijkstra.h"

file_t * dijkstra(graph_t * graphe, int rac, int dest) {
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
    while(!tasVideDijkstra(tas) && (e.som != dest)) {
        enfiler(file, e.som);
        for(int i = 0; i < graphe->listeAretes->tailleCourante; i++) {
            if((graphe->listeAretes->array[i]->n1.valeur == e.som) && (d[graphe->listeAretes->array[i]->n2.valeur] > d[e.som] + graphe->listeAretes->array[i]->poids)) {
                d[graphe->listeAretes->array[i]->n2.valeur] = d[e.som] + graphe->listeAretes->array[i]->poids;
                parent[graphe->listeAretes->array[i]->n2.valeur] = e.som;
                modifValeurTasDijkstra(tas, graphe->listeAretes->array[i]->n2.valeur, d[e.som] + graphe->listeAretes->array[i]->poids);
            }
            else if((graphe->listeAretes->array[i]->n2.valeur == e.som) && (d[graphe->listeAretes->array[i]->n1.valeur] > d[e.som] + graphe->listeAretes->array[i]->poids)) {
                d[graphe->listeAretes->array[i]->n1.valeur] = d[e.som] + graphe->listeAretes->array[i]->poids;
                parent[graphe->listeAretes->array[i]->n1.valeur] = e.som;
                modifValeurTasDijkstra(tas, graphe->listeAretes->array[i]->n1.valeur, d[e.som] + graphe->listeAretes->array[i]->poids);
            }
        }
        e = suppressionRacineDijkstra(tas);
    }
    enfiler(file, dest);
    libererTasDijkstra(tas);
    free(d);
    free(parent);
    return file;
}
