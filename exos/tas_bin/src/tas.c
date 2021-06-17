#include "../headers/tas.h"

tas_t * creerTas() {
    tas_t * tas = malloc(sizeof(tas_t));
    tas->array = malloc(DEFAULT_LENGTH * sizeof(int));
    tas->length = DEFAULT_LENGTH;
    tas->indexToInsert = 0;
    return tas;
}

void reallocTas(tas_t * tas, float coeff) {
	int nouvelle_taille = tas->length * coeff;
	if(nouvelle_taille < DEFAULT_LENGTH){
		nouvelle_taille = DEFAULT_LENGTH;
	}
	int * nouveau_tab = malloc(nouvelle_taille * sizeof(int));
	memcpy(nouveau_tab, tas->array, (tas->indexToInsert) * sizeof(int));
	free(tas->array);
	tas->array = nouveau_tab;
    tas->length = nouvelle_taille;
}

void ajoutTas(tas_t * tas, int valeur) {
	if(tas->indexToInsert >= tas->length) {
		reallocTas(tas, 2);
	}
    int i = tas->indexToInsert;
    while((i > 0) && (valeur < tas->array[(i-1)/2])) {
        tas->array[i] = tas->array[(i-1)/2];
        i = (i-1)/2;
    }
    tas->array[i] = valeur;
    tas->indexToInsert++;
}

int racineTas(tas_t * tas) {
    return tas->array[0];
}

int suppressionRacine(tas_t * tas) {
    int i = 0;
    int r = tas->array[0];
    int e = tas->array[tas->indexToInsert-1];
    tas->indexToInsert--;
    while((2*i + 1 < tas->indexToInsert) || (2*i + 2 < tas->indexToInsert)) {
        if((2*i + 1 < tas->indexToInsert) && (tas->array[2*i + 1] < tas->array[2*i + 2])) {
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

void libererTas(tas_t * tas) {
    free(tas->array);
    free(tas);
}


void tri_tas(int * tab, int taille) {
    tas_t * tas = creerTas();
    for(int i = 0; i < taille; i++) {
        ajoutTas(tas, tab[i]);
    }
    for(int i = 0; i < taille; i++) {
        tab[i] = racineTas(tas);
        suppressionRacine(tas);
    }
    libererTas(tas);
}

void afficherTas(tas_t * tas){
	int i;
	for(i = 0; i < tas->indexToInsert; i++){
		printf("%d\n", tas->array[i]);
	}
}