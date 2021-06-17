#include "../headers/union_find.h"


union_find_t * createUnionFind(int size, int * erreur){
    *erreur = 0;
    union_find_t * unionFind;
    unionFind = malloc(sizeof(union_find_t));
    if(unionFind == NULL) {
        *erreur = 1;
    }
    else{
        unionFind->partition = malloc(size*sizeof(int));
        if(unionFind->partition == NULL) {
            *erreur = 2;
        }
        else {
            unionFind->level = malloc(size*sizeof(int));
            if(unionFind->partition == NULL) {
                *erreur = 3;
            }
            else {
                unionFind->size = size;
            }
        }
    }
    return unionFind;
}


void freeUnionFind(union_find_t * unionFind) {
    if(unionFind){
        if(unionFind->partition){
            free(unionFind->partition);
            unionFind->partition = NULL;
        }
        if(unionFind->level){
            free(unionFind->level);
            unionFind->level = NULL;
        }
        free(unionFind);
        unionFind = NULL;
    }
}
void initUnionFind(union_find_t * unionFind){
    for(int i = 0; i < unionFind->size; ++i){
        unionFind->level[i] = 0;
        unionFind->partition[i] = i;
    }
}

void printUnionFind(union_find_t * unionFind) {
    printf("-----------------------------------------------\n");
    printf("Hauteur :\n");
    for(int i = 0; i < unionFind->size; i++){
        printf("%d - ",unionFind->level[i]);
    }
    printf("\nValeur :\n");
    for(int i = 0; i < unionFind->size; i++){
        printf("%d - ",unionFind->partition[i]);
    }
    printf("\n\n");
    printf("-----------------------------------------------\n\n");

}

 int rootNodeUnionFind(union_find_t * unionFind, int node){
    while(node != unionFind->partition[node]){
        node = unionFind->partition[node];
    }
    return node;
 }

 void fusionUnionFind(union_find_t * unionFind, int x, int y) {
    int xRoot, yRoot;
    if(x < unionFind->size && y < unionFind->size) {
        xRoot = rootNodeUnionFind(unionFind, x);
        yRoot = rootNodeUnionFind(unionFind, y);
        if (xRoot != yRoot) { // Ils sont dans la même classe
            if (unionFind->level[xRoot] < unionFind->level[yRoot]) { //
                unionFind->partition[xRoot] = yRoot;
                unionFind->level[xRoot]--;

            } else {
                unionFind->partition[yRoot] = xRoot;
                unionFind->level[yRoot]--;
                if (unionFind->level[xRoot] == unionFind->level[yRoot]) {
                    unionFind->level[xRoot]++;
                }
            }
        }
    }
    else{
        printf("Impossible de fusionner les classes de %d et %d\n",x,y);
    }
}

void printClassUnionFind(union_find_t * unionFind, int node){
    int root;
    root = rootNodeUnionFind(unionFind,node);
    printf("{");
    for(int i = 0; i < unionFind->size; i++) {
        if(rootNodeUnionFind(unionFind,unionFind->partition[i]) == root)
        {
            printf("%d,",i);
        }
    }
    printf("\b}");
}

void printAllClassesUnionFind(union_find_t * unionFind){
    printf("\n{");
    for(int i =0; i< unionFind->size; i++){
        if(unionFind->level[i] == 0){
            printClassUnionFind(unionFind,i);
            printf(",");
        }
    }
    printf("\b}\n");
}