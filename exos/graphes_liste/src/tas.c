#include "../headers/tas.h"

tas_t * creerTas() {
    tas_t * tas = malloc(sizeof(tas_t));
    tas->array = malloc(DEFAULT_LENGTH * sizeof(elem_tas_t));
    tas->length = DEFAULT_LENGTH;
    tas->indexToInsert = 0;
    return tas;
}

void reallocTas(tas_t * tas, float coeff) {
	int nouvelle_taille = tas->length * coeff;
	if(nouvelle_taille < DEFAULT_LENGTH){
		nouvelle_taille = DEFAULT_LENGTH;
	}
	elem_tas_t * nouveau_tab = malloc(nouvelle_taille * sizeof(elem_tas_t));
	memcpy(nouveau_tab, tas->array, (tas->indexToInsert) * sizeof(elem_tas_t));
	free(tas->array);
	tas->array = nouveau_tab;
    tas->length = nouvelle_taille;
}

void ajoutTas(tas_t * tas, elem_tas_t valeur) {
	if(tas->indexToInsert >= tas->length) {
		reallocTas(tas, 2);
	}
    int i = tas->indexToInsert;
    while((i > 0) && (valeur.poids < tas->array[(i-1)/2].poids)) {
        tas->array[i] = tas->array[(i-1)/2];
        i = (i-1)/2;
    }
    tas->array[i] = valeur;
    tas->indexToInsert++;
}

elem_tas_t racineTas(tas_t * tas) {
    return tas->array[0];
}

elem_tas_t suppressionRacine(tas_t * tas) {
    int i = 0;
    elem_tas_t r = tas->array[0];
    elem_tas_t e = tas->array[tas->indexToInsert-1];
    tas->indexToInsert--;
    while((2*i + 1 < tas->indexToInsert) || (2*i + 2 < tas->indexToInsert)) {
        if((2*i + 1 < tas->indexToInsert) && (tas->array[2*i + 1].poids < tas->array[2*i + 2].poids)) {
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
	    reallocTas(tas, 0.5);
    }
    return r;
}

int tasVide(tas_t * tas) {
    return (tas->indexToInsert == 0);
}

void libererTas(tas_t * tas) {
    free(tas->array);
    free(tas);
}
