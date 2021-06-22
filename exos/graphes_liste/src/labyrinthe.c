#include "../headers/labyrinthe.h"

labyrinthe_t * creerLabyrintheQqc(int lignes, int colonnes, double proba){
	arete_t ** tableauArete;
	tableauArete = genererGrapheGrille(lignes, colonnes);
	labyrinthe_t * labyrinthe;
	labyrinthe = malloc(sizeof(labyrinthe_t));
	labyrinthe->colonnes = colonnes;
	labyrinthe->lignes = lignes;
	labyrinthe->graphe = nouveau_graphe(lignes*colonnes);
	kruskalFisherYatesProba(tableauArete, labyrinthe, proba);
	return labyrinthe;
}

void kruskalFisherYatesProba(arete_t ** tableauArete, labyrinthe_t * labyrinthe, double proba){
    int lignes = labyrinthe->lignes, colonnes = labyrinthe->colonnes, err;
    double alpha;
    maillon_arete_t* courant, * temp;
    maillon_arete_t * listeAreteTemp = fisherYates(tableauArete, lignes, colonnes);


    partition_t* partArbre = createPartition(lignes*colonnes, &err);
    initPartition(partArbre);
    courant = listeAreteTemp;
    while(courant != NULL){
        alpha = rand()%891975; // ;)
        alpha/=891975.0;
        if(fusionPartition(partArbre, courant->arete->n1.valeur, courant->arete->n2.valeur) == 0){
            insertionTeteArete(&labyrinthe->graphe->listeAretes, creerMaillonArete(courant->arete));
        }else if(alpha <= proba){
            insertionTeteArete(&labyrinthe->graphe->listeAretes, creerMaillonArete(courant->arete));
        }
        else{
            free(courant->arete);
        }
        temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    freePartition(partArbre);
}

maillon_arete_t * tableauVersListeAretes(arete_t ** tableauAretes, int lignes, int colonnes){
	maillon_arete_t * tete;
	tete = NULL;
	int i, m = 2*lignes*colonnes - lignes - colonnes;
	for(i = 0; i < m; i++){
		insertionTeteArete(&tete, creerMaillonArete(tableauAretes[i]));
	}
	free(tableauAretes);
	return tete;
}

maillon_arete_t * fisherYates(arete_t ** tableauAretes, int lignes, int colonnes){
	arete_t * temp;
	int i, j, m = 2*lignes*colonnes - lignes - colonnes;
	for(i = m - 1; i > 0; i--){
		j = rand() % (i +1);
		temp = tableauAretes[j];
		tableauAretes[j] = tableauAretes[i];
		tableauAretes[i] = temp;
	}
	return tableauVersListeAretes(tableauAretes, lignes, colonnes);
}