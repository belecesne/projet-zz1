#include "../headers/tas.h"

tas_t* creerTas(int size){
	tas_t* tas = malloc(sizeof(tas_t));
	tas->array = malloc(size * sizeof(type_tas_t));
	tas->length = size;
	tas->indexToInsert = 0;
	return tas;
}

void reallocTas(tas_t* tas, float coeff){
	int nouvelle_taille = tas->length * coeff;
	if(nouvelle_taille < DEFAULT_LENGTH){
		nouvelle_taille = DEFAULT_LENGTH;
	}
	type_tas_t * nouveau_tab = malloc(nouvelle_taille * sizeof(type_tas_t));
	memcpy(nouveau_tab, tas->array, (tas->indexToInsert) * sizeof(type_tas_t));
	free(tas->array);
	tas->array = nouveau_tab;
	tas->length = nouvelle_taille;
}

void ajoutTas(tas_t* tas, type_tas_t valeur){
	if(tas->indexToInsert >= tas->length){
		reallocTas(tas, 2);
	}
	int i = tas->indexToInsert;
	while((i > 0) && (valeur->poids < tas->array[(i - 1) / 2]->poids)){
		tas->array[i] = tas->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	tas->array[i] = valeur;
	tas->indexToInsert++;
}

type_tas_t racineTas(tas_t* tas){
	return tas->array[0];
}

type_tas_t suppressionRacine(tas_t* tas, int sorted){
	int i = 0;
	type_tas_t r = tas->array[0];
	type_tas_t e = tas->array[tas->indexToInsert - 1];
	tas->indexToInsert--;
	while((2 * i + 1 < tas->indexToInsert) || (2 * i + 2 < tas->indexToInsert)){
		if((2 * i + 1 < tas->indexToInsert) && (tas->array[2 * i + 1]->poids < tas->array[2 * i + 2]->poids)){
			tas->array[i] = tas->array[2 * i + 1];
			i = 2 * i + 1;
		} else{
			tas->array[i] = tas->array[2 * i + 2];
			i = 2 * i + 2;
		}
	}
	tas->array[i] = e;
	if(tas->indexToInsert <= 0.1 * tas->length && !sorted){
		reallocTas(tas, 0.5);
	}
	return r;
}

void libererTas(tas_t* tas){
	free(tas->array);
	free(tas);
}

int tasVide(tas_t * tas) {
	return (tas->indexToInsert == 0);
}