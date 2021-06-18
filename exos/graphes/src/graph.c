#include "../headers/graph.h"

int ** generateRandomGraph(int nbVertices) {
    int ** adjMat = malloc(nbVertices * sizeof(int*));
    int nb_edges = 0;
    for(int i = 0; i < nbVertices; i++) {
        adjMat[i] = calloc(nbVertices, sizeof(int));
        for(int j = 0; j <= i && nb_edges<10; j++) {
            int nb = rand()%2;
            if(nb) {
                adjMat[i][j] = nb;
                adjMat[j][i] = nb;
                nb_edges++;
            }
        } 
    }
    return adjMat;
}

void generateGraphvizGraph(int ** adjMat, int nbVertices, char * fileName) {
    char fullFileName[BUFSIZ];
    sprintf(fullFileName, "%s.dot", fileName);
    FILE * dotFile = fopen(fullFileName, "w");
    fputs("graph G {\n", dotFile);
    for(int i = 0; i < nbVertices; i++) {
        fprintf(dotFile, "  \"%d\";\n", i);
        for(int j = 0; j <= i; j++) {
            if(adjMat[i][j]) {
                fprintf(dotFile, "  \"%d\" -- \"%d\";\n", i, j);
            }
        }
    }
    fputs("}\n", dotFile);
    fclose(dotFile);
    sprintf(fullFileName, "dot -Tsvg %s.dot > %s.svg", fileName, fileName);
    system(fullFileName);
}

union_find_t * getGraphUnionFind(int ** adjMat, int nbVertices) {
    int err;
    union_find_t * part = createUnionFind(15, &err);
    initUnionFind(part);
    for(int i = 0; i < nbVertices; i++) {
        for(int j = 0; j <= i; j++) {
            if((adjMat[i][j]) && (!isInSameClass(i, j, part))) {
                fusionUnionFind(part, i, j);
            }
        }
    }
    return part;
}

void generateConnectedComponents(int ** adjMat, int nbVertices, union_find_t * part, char * fileName) {
    int ** ufRpr = generateUnionFindRepresentation(part);
    for(int i = 0; i < nbVertices; i++) {
        if(ufRpr[i] != NULL) {
            char buffer[BUFSIZ];
            sprintf(buffer, "%s_%d.dot", fileName, i);
            FILE * dotFile = fopen(buffer, "w");
            fputs("graph D {\n", dotFile);
            for(int j = 0; j < nbVertices; j++) {
                if(ufRpr[i][j]) {
                    fprintf(dotFile, "  \"%d\";\n", j);
                    for(int k = 0; k <= j; k++) {
                        if(adjMat[j][k]) {
                            fprintf(dotFile, "  \"%d\" -- \"%d\";\n", j, k);
                        }
                    }
                }
            }
            fputs("}\n", dotFile);
            fclose(dotFile);
            sprintf(buffer, "dot -Tsvg %s_%d.dot > %s_%d.svg", fileName, i, fileName, i);
            system(buffer);
        }
    }
}