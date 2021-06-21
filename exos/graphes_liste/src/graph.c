#include "../headers/graph.h"


graph_t* nouveau_graphe(int nbNoeuds){
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

void liberer_graphe(graph_t* graphe){
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
		printf("%p %p %p\n", cour->arete, cour->arete->n1, cour->arete->n2);
		fprintf(dotFile, "  \"%d\" -- \"%d\";\n", cour->arete->n1->valeur, cour->arete->n2->valeur);
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
		fusionPartition(part, courant->arete->n1->valeur, courant->arete->n2->valeur);
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
				if(currNode == areteCourante->arete->n1->valeur){
					fprintf(dotFile, "  \"%d\" -- \"%d\";\n", currNode, areteCourante->arete->n2->valeur);
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

void genererGrapheGrille(int lignes, int colonnes){
	graph_t* graphe = nouveau_graphe(lignes * colonnes);
	noeud_t ** noeuds;
	int i, j, noeud, n, s, w, e;
	noeuds = malloc(graphe->nbNoeuds * sizeof(noeud_t *));
	for(i = 0; i < graphe->nbNoeuds; i++){
		noeuds[i] = creerNoeud(i);
	}
	for(i = 0; i < lignes; i++){
		for(j = (i % 2 == 0 ? 0 : 1); j < colonnes; j += 2){
			noeud = i * colonnes + j;
			n = (i - 1) * colonnes + j;
			s = (i + 1) * colonnes + j;
			w = i * colonnes + j - 1;
			e = i * colonnes + j + 1;
			printf("i = %d, j = %d, noeud = %d, n = %d, s= %d, w = %d, e = %d\n", i,j,noeud, n,s,w,e);
			if(n >= 0){
				printf("n = %d\n", n);
				insertionArrete(graphe, creerArete(noeuds[n], noeuds[noeud], 1));
			}
			if(s < graphe->nbNoeuds){
				printf("s = %d\n", s);
				insertionArrete(graphe, creerArete(noeuds[s], noeuds[noeud], 1));
			}
			if(w / colonnes == i && w >= 0){
				printf("w = %d\n", w);
				insertionArrete(graphe, creerArete(noeuds[w], noeuds[noeud], 1));
			}
			if(e / colonnes == i && e < graphe->nbNoeuds){
				printf("e = %d\n", e);
				insertionArrete(graphe, creerArete(noeuds[e], noeuds[noeud], 1));
			}
		}
	}
	generateGraphvizGraph(graphe, "graphe_grille");
}