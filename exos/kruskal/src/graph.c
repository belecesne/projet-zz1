#include "../headers/graph.h"


graph_t* nouveauGraphe(int nbNoeuds){
	graph_t* graph;
	graph = malloc(sizeof(graph_t));
	if(graph){
		graph->nbNoeuds = nbNoeuds;
		graph->listeAretes = NULL;
	}
	return graph;
}

void insertionArrete(graph_t* graphe, arete_t* arete){
	insertionTeteArete(&(graphe->listeAretes), creerMaillonArete(arete));
}

void libererGraphe(graph_t* graphe){
	libererListeArretes(graphe->listeAretes);
	free(graphe);
}

void generateGraphvizGraph(graph_t* graphe, char* filename){
	char buffer[BUFSIZ];
	sprintf(buffer, "%s.dot", filename);
	FILE* dotFile = fopen(buffer, "w");
	fputs("graph G {\n", dotFile);
	for(int i = 0; i < graphe->nbNoeuds; i++){
		fprintf(dotFile, "  \"%d\";\n", i);
	}
	maillon_arete_t* cour = graphe->listeAretes;
	while(cour != NULL){
		fprintf(dotFile, "  \"%d\" -- \"%d\";\n", cour->arete->n1.valeur,
		        cour->arete->n2.valeur);
		cour = cour->suivant;
	}

	fputs("}\n", dotFile);
	fclose(dotFile);
	sprintf(buffer,
	        "dot -Tsvg %s.dot > %s.svg", filename, filename);
	system(buffer);
}

partition_t* getParitionFromGraph(graph_t* graphe){
	int err;
	partition_t* part = createPartition(graphe->nbNoeuds, &err);
	initPartition(part);
	maillon_arete_t* courant;
	courant = graphe->listeAretes;
	while(courant != NULL){
		fusionPartition(part, courant->arete->n1.valeur, courant->arete->n2.valeur);
		courant = courant->suivant;
	}
	return part;
}

void generateConnectedComponents(graph_t* graphe, char* filename){
	partition_t* part = getParitionFromGraph(graphe);
	maillon_classe_t* classes;
	maillon_classe_t* classeCourante, * tempClasse;
	maillon_arete_t* areteCourante;
	maillon_t* elementCourant;
	int currNode;
	char buffer[BUFSIZ];
	classes = getAllClasses(part);
	classeCourante = classes;
	while(classeCourante != NULL){
		sprintf(buffer, "%s_%d.dot", filename, classeCourante->classe->racine);
		FILE* dotFile = fopen(buffer, "w");
		fputs("graph G {\n", dotFile);
		elementCourant = classeCourante->classe->tete;
		while(elementCourant != NULL){
			currNode = elementCourant->valeur;
			fprintf(dotFile, "  \"%d\";\n", currNode);
			areteCourante = graphe->listeAretes;
			while(areteCourante != NULL){
				if(currNode == areteCourante->arete->n1.valeur){
					fprintf(dotFile, "  \"%d\" -- \"%d\" [weight=%d, label=\"%d\"];\n", currNode,
					        areteCourante->arete->n2.valeur, areteCourante->arete->poids, areteCourante->arete->poids);
				}
				areteCourante = areteCourante->suivant;
			}
			elementCourant = elementCourant->suivant;
		}
		fputs("}\n", dotFile);
		fclose(dotFile);
		sprintf(buffer,
		        "dot -Tsvg %s_%d.dot > %s_%d.svg", filename, classeCourante->classe->racine, filename,
		        classeCourante->classe->racine);
		system(buffer);
		tempClasse = classeCourante;
		classeCourante = classeCourante->suivant;
		free(tempClasse);
	}
	freePartition(part);
}

graph_t* kruskal(graph_t* graphe){
	tas_t* tas = creerTas(graphe->nbNoeuds);
	maillon_arete_t* courant = graphe->listeAretes;
	arete_t* areteMin, * nouvelleArete;
	while(courant != NULL){
		ajoutTas(tas, courant->arete);
		courant = courant->suivant;
	}
	int err;
	partition_t* partArbre = createPartition(graphe->nbNoeuds, &err);
	initPartition(partArbre);
	graph_t* arbre = nouveauGraphe(graphe->nbNoeuds);
	while(!tasVide(tas)){
		areteMin = suppressionRacine(tas, 0);
		if(fusionPartition(partArbre, areteMin->n1.valeur, areteMin->n2.valeur) == 0){
			nouvelleArete = creerArete(areteMin->n1, areteMin->n2, areteMin->poids);
			insertionTeteArete(&arbre->listeAretes, creerMaillonArete(nouvelleArete));
		}
	}
	libererTas(tas);
	freePartition(partArbre);
	return arbre;
}
