#include "../headers/tas_dijkstra.h"

tas_dijkstra_t * creerTasDijktra() {
    tas_dijkstra_t * tas = malloc(sizeof(tas_dijkstra_t));
    tas->array = malloc(DEFAULT_LENGTH_DIJKSTRA * sizeof(elem_tas_dijkstra_t));
    tas->length = DEFAULT_LENGTH_DIJKSTRA;
    tas->indexToInsert = 0;
    return tas;
}

void reallocTasDijkstra(tas_dijkstra_t * tas, float coeff) {
	int nouvelle_taille = tas->length * coeff;
	if(nouvelle_taille < DEFAULT_LENGTH_DIJKSTRA){
		nouvelle_taille = DEFAULT_LENGTH_DIJKSTRA;
	}
	elem_tas_dijkstra_t * nouveau_tab = malloc(nouvelle_taille * sizeof(elem_tas_dijkstra_t));
	memcpy(nouveau_tab, tas->array, (tas->indexToInsert) * sizeof(elem_tas_dijkstra_t));
	free(tas->array);
	tas->array = nouveau_tab;
    tas->length = nouvelle_taille;
}

void ajoutTasDijkstra(tas_dijkstra_t * tas, elem_tas_dijkstra_t valeur) {
	if(tas->indexToInsert >= tas->length) {
		reallocTasDijkstra(tas, 2);
	}
    int i = tas->indexToInsert;
    while((i > 0) && (valeur.dist < tas->array[(i-1)/2].dist)) {
        tas->array[i] = tas->array[(i-1)/2];
        i = (i-1)/2;
    }
    tas->array[i] = valeur;
    tas->indexToInsert++;
}

elem_tas_dijkstra_t racineTasDijktra(tas_dijkstra_t * tas) {
    return tas->array[0];
}

elem_tas_dijkstra_t suppressionRacineDijkstra(tas_dijkstra_t * tas) {
    int i = 0;
    elem_tas_dijkstra_t r = tas->array[0];
    elem_tas_dijkstra_t e = tas->array[tas->indexToInsert-1];
    tas->indexToInsert--;
    while((2*i + 1 < tas->indexToInsert) || (2*i + 2 < tas->indexToInsert)) {
        if((2*i + 1 < tas->indexToInsert) && (tas->array[2*i + 1].dist < tas->array[2*i + 2].dist)) {
            tas->array[i] = tas->array[2*i + 1];
            i = 2*i + 1;
        }
        else {
            tas->array[i] = tas->array[2*i + 2];
            i = 2*i + 2;
        }
    }
    tas->array[i] = e;
    if(tas->indexToInsert <= 0.1 * tas->length){
	    reallocTasDijkstra(tas, 0.5);
    }
    return r;
}

int tasVideDijkstra(tas_dijkstra_t * tas) {
    return (tas->indexToInsert == 0);
}

void libererTasDijkstra(tas_dijkstra_t * tas) {
    free(tas->array);
    free(tas);
}

void modifValeurTasDijkstra(tas_dijkstra_t * tas, int noeud, int nouvelle_distance) {
    int i = 0;
    while((i < tas->indexToInsert) && (tas->array[i].som != noeud)) {
        i++;
    }
    if(tas->array[i].dist > nouvelle_distance) {
        while((i > 0) && (nouvelle_distance < tas->array[(i-1)/2].dist)) {
            tas->array[i] = tas->array[(i-1)/2];
            i = (i-1)/2;
        }
    }
    else {
        while((tas->array[2*i + 1].dist > nouvelle_distance) && (tas->array[2*i + 2].dist > nouvelle_distance)) {
            if(tas->array[2*i + 1].dist < tas->array[2*i + 2].dist) {
                tas->array[i] = tas->array[2*i + 1];
                i = 2*i + 1;
            }
            else {
                tas->array[i] = tas->array[2*i + 2];
                i = 2*i + 2;
            }
        }
    }
    elem_tas_dijkstra_t e = {noeud, nouvelle_distance};
    tas->array[i] = e;
}
