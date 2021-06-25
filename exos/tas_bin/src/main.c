#include "../headers/tas.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

int inf(const void* a, const void* b){
	return (*(int*)a - *(int*)b);
}

void testFunctions(int lengthToTest){
	printf("Test avec une instance de %d d'entiers\n", lengthToTest);
	type_tas_t * tab = malloc(lengthToTest * sizeof(type_tas_t));
	for(int i = 0; i < lengthToTest; i++){
		tab[i] = rand() % 100;
	}
	type_tas_t * arrayCopy = malloc(lengthToTest * sizeof(type_tas_t));
	memcpy(arrayCopy, tab, lengthToTest * sizeof(type_tas_t));
	printf("Temps mis pour la fonction qsort:\n");
	clock_t begin = clock();
	qsort(tab, lengthToTest, sizeof(type_tas_t), inf);
	clock_t end = clock();
	printf("Fini en %ld ms\n", (unsigned long)((end - begin) * 1000 / CLOCKS_PER_SEC));
	printf("Temps mis pour l'algorithme de tri par tas\n");
	begin = clock();
	tri_tas(arrayCopy, lengthToTest);
	end = clock();
	printf("Fini en %ld ms\n\n", (unsigned long)((end - begin) * 1000 / CLOCKS_PER_SEC));
	free(tab);
	free(arrayCopy);
}

int main(){
	tas_t* tas = creerTas(10);
	for(int i = 31; i > 0; i--){
		ajoutTas(tas, i);
	}

	afficherTas(tas);

	printf("------------------------\n");

	for(int j = 1; j < 28; j++){
		suppressionRacine(tas, 0);
	}

	afficherTas(tas);

	libererTas(tas);


	srand(time(NULL));
	testFunctions(10);
	testFunctions(100);
	testFunctions(1000);
	testFunctions(10000);
	testFunctions(100000);
	testFunctions(1000000);
}