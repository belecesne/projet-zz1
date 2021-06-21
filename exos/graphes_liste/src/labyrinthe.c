#include "../headers/labyrinthe.h"

labyrinthe_t * creerLabyrintheQqc(int lignes, int colonnes, double proba){
	graph_t *graphe;
	graphe = genererGrapheGrille(lignes, colonnes);
	labyrinthe_t * labyrinthe;
	labyrinthe = malloc(sizeof(labyrinthe_t));
	labyrinthe->colonnes = colonnes;
	labyrinthe->lignes = lignes;
	labyrinthe->graphe = nouveau_graphe(graphe->nbNoeuds);
	kruskalFisherYatesProba(graphe, labyrinthe, proba);
	return labyrinthe;
}

void kruskalFisherYatesProba(graph_t* graphe, labyrinthe_t * labyrinthe, double proba){
    int lignes = labyrinthe->lignes, colonnes = labyrinthe->colonnes, err;
    double alpha;
    maillon_arete_t* courant, * temp;
    fisherYates(graphe, lignes, colonnes);


    partition_t* partArbre = createPartition(graphe->nbNoeuds, &err);
    initPartition(partArbre);
    courant = graphe->listeAretes;
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
    free(graphe);
    freePartition(partArbre);
}

arete_t ** listeVersTableauAretes(graph_t * graphe, int lignes, int colonnes){
	maillon_arete_t  * courant, * temp;
	arete_t ** tableauAretes;
	int i = 0;
	courant = graphe->listeAretes;
	tableauAretes = malloc((2*lignes*colonnes - lignes - colonnes) * sizeof(arete_t *));
	if(tableauAretes != NULL){
		while(courant != NULL){
			tableauAretes[i] = courant->arete;
			temp = courant->suivant;
			free(courant);
			courant = temp;
			i++;
		}
	}
	return tableauAretes;
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

void fisherYates(graph_t * graphe, int lignes, int colonnes){
	arete_t ** tableauAretes;
	arete_t * temp;
	int i, j, m = 2*lignes*colonnes - lignes - colonnes;
	tableauAretes = listeVersTableauAretes(graphe, lignes, colonnes);
	for(i = m - 1; i > 0; i--){
		j = rand() % (i +1);
		temp = tableauAretes[j];
		tableauAretes[j] = tableauAretes[i];
		tableauAretes[i] = temp;
	}
	graphe->listeAretes = tableauVersListeAretes(tableauAretes, lignes, colonnes);
}