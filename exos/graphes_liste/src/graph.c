#include "../headers/graph.h"


graph_t *nouveau_graphe() {
    graph_t * graph;
    graph = malloc(sizeof(graph_t));
    if (graph) {
        graph->liste = NULL;
        graph->nbNoeuds = 0;
    }
    return graph;
}

void insertionArrete(graph_t * graphe, maillon_t *maillon) {
    if((maillon != NULL) && (maillon->noeud1 < graphe->nbNoeuds) && (maillon->noeud2 < graphe->nbNoeuds)) {
        maillon->suivant = graphe->liste;
        graphe->liste = maillon;
    }
}

void liberer_graphe(graph_t * graphe) {
    maillon_t *maillon_courant = graphe->liste;
    maillon_t *sauvegarde_adresse_maillon;
    while (maillon_courant != NULL) {
        sauvegarde_adresse_maillon = maillon_courant;
        maillon_courant = sauvegarde_adresse_maillon->suivant;
        free(sauvegarde_adresse_maillon);
    }
    free(graphe);
    graphe = NULL;
}

void generateGraphvizGraph(graph_t * graphe, char * filename) {
    char buffer[BUFSIZ];
    sprintf(buffer, "%s.dot", filename);
    FILE * dotFile = fopen(buffer, "w");
    fputs("graph G {\n", dotFile);
    for(int i = 0; i < graphe->nbNoeuds; i++) {
        fprintf(dotFile, "  \"%d\";\n", i);
    }
    maillon_t * cour = graphe->liste;
    while(cour != NULL) {
        fprintf(dotFile, "  \"%d\" -- \"%d\";\n", cour->noeud1, cour->noeud2);
        cour = cour->suivant;
    }
    fputs("}\n", dotFile);
    fclose(dotFile);
    sprintf(buffer, "dot -Tsvg %s.dot > %s.svg", filename, filename);
    system(buffer);
}