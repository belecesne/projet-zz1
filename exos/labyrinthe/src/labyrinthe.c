#include "../headers/labyrinthe.h"

void genererTableauCellule(labyrinthe_t* lab, int weight, int height){
	int i, indiceN1, indiceN2;
    for(i = 0; i < lab->lignes * lab->colonnes;i++){
        lab->tableauCellules[i] = 0;
    }
	for(i = 0; i < lab->graphe->listeAretes->tailleCourante;
	    i++){
            indiceN1 = lab->graphe->listeAretes->array[i]->n1.valeur;
            indiceN2 = lab->graphe->listeAretes->array[i]->n2.valeur;
		if(lab->tableauCellules[indiceN1] == 0){
			lab->tableauCellules[indiceN1] = creerCelluleDepuisNoeud(
					lab->graphe->listeAretes->array[i]->n1, weight, height, lab->colonnes);
		}
		if(lab->tableauCellules[indiceN2] == 0){
			lab->tableauCellules[indiceN2] = creerCelluleDepuisNoeud(
					lab->graphe->listeAretes->array[i]->n2, weight, height, lab->colonnes);
		}
	}
	creerMur(lab);
}

labyrinthe_t* creerLabyrintheQqc(int lignes, int colonnes, int weight, int height){
	graph_t* graphe;
	graphe = genererGrapheGrille(lignes, colonnes);
	labyrinthe_t* labyrinthe;
	labyrinthe = malloc(sizeof(labyrinthe_t));
	labyrinthe->colonnes = colonnes;
	labyrinthe->lignes = lignes;
	labyrinthe->graphe = nouveauGraphe(lignes * colonnes);
	labyrinthe->tableauCellules = calloc(lignes * colonnes, sizeof(cellule_t*));
	kruskalFisherYates(graphe, labyrinthe);

	genererTableauCellule(labyrinthe, weight, height);
	return labyrinthe;
}

void kruskalFisherYates(graph_t* graphe, labyrinthe_t* labyrinthe){
	int lignes = labyrinthe->lignes, colonnes = labyrinthe->colonnes, err, i = 0;
	fisherYates(graphe);
	partition_t* partArbre = createPartition(lignes * colonnes, &err);
	initPartition(partArbre);
	while(i < graphe->listeAretes->tailleCourante){
		if(fusionPartition(partArbre, graphe->listeAretes->array[i]->n1.valeur,
		                   graphe->listeAretes->array[i]->n2.valeur) == 0){
			insererQueueVecteurArete(labyrinthe->graphe->listeAretes, graphe->listeAretes->array[i]);
		} else{
			supprimerVecteurArete(&graphe->listeAretes, i);
			i--;
		}
		i++;
	}
	freePartition(partArbre);
	libererGraphe(graphe);
}

void kruskalFisherYatesProba(graph_t* graphe, labyrinthe_t* labyrinthe, double proba){
	int lignes = labyrinthe->lignes, colonnes = labyrinthe->colonnes, err, i = 0;
	double alpha;
	fisherYates(graphe);

	partition_t* partArbre = createPartition(lignes * colonnes, &err);
	initPartition(partArbre);
	while(i < graphe->listeAretes->tailleCourante){
		alpha = rand() % 891975; // ;)
		alpha /= 891975.0;
		if(fusionPartition(partArbre, graphe->listeAretes->array[i]->n1.valeur,
		                   graphe->listeAretes->array[i]->n2.valeur) == 0){
			insererQueueVecteurArete(labyrinthe->graphe->listeAretes, graphe->listeAretes->array[i]);
		} else if(alpha <= proba){
			insererQueueVecteurArete(labyrinthe->graphe->listeAretes, graphe->listeAretes->array[i]);
		} else{
			supprimerVecteurArete(&graphe->listeAretes, i);
			i--;
		}
		i++;
	}
	freePartition(partArbre);
	libererGraphe(graphe);
}


void fisherYates(graph_t* graphe){
	arete_t* temp;
	int i, j, m = graphe->listeAretes->tailleCourante;
	for(i = m - 1; i > 0; i--){
		j = rand() % (i + 1);
		temp = graphe->listeAretes->array[j];
		graphe->listeAretes->array[j] = graphe->listeAretes->array[i];
		graphe->listeAretes->array[i] = temp;
	}
}

void libererLabyrinthe(labyrinthe_t* lab){
	int i;
	for(i = 0; i < lab->graphe->listeAretes->tailleCourante; i++){
		free(lab->graphe->listeAretes->array[i]);
	}
	libererGraphe(lab->graphe);
	free(lab);
}

void creerMur(labyrinthe_t* labyrinthe){
	int k, colonnes;
	int i,j,x,y, indiceN1, indiceN2;
    colonnes = labyrinthe->colonnes;
	for(k = 0; k < labyrinthe->graphe->listeAretes->tailleCourante; k++){
        indiceN1 = labyrinthe->graphe->listeAretes->array[k]->n1.valeur;
        indiceN2 = labyrinthe->graphe->listeAretes->array[k]->n2.valeur;

	    i = (labyrinthe->tableauCellules[indiceN1]->noeud.valeur)/colonnes;
	    j = (labyrinthe->tableauCellules[indiceN1]->noeud.valeur)%colonnes;
	    x = (labyrinthe->tableauCellules[indiceN2]->noeud.valeur)/colonnes;
	    y = (labyrinthe->tableauCellules[indiceN2]->noeud.valeur)%colonnes;

        if (j == y) {
            labyrinthe->tableauCellules[indiceN1]->wall+=2;
            labyrinthe->tableauCellules[indiceN2]->wall+=1;
        }
        if(i == x){
            labyrinthe->tableauCellules[indiceN1]->wall+=4;
            labyrinthe->tableauCellules[indiceN2]->wall+=8;
        }
	}
}