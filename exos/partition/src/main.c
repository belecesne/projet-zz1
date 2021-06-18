#include "../headers/main.h"


int main() {

    int erreur = 0;
    union_find_t *unionFind;
    unionFind = createUnionFind(DEFAULT_UNION_FIND_SIZE, &erreur);
    if (!erreur) {


        initUnionFind(unionFind);

        fusionUnionFind(unionFind, 0, 1);

        fusionUnionFind(unionFind, 2, 3);

        fusionUnionFind(unionFind, 10, 3);

        fusionUnionFind(unionFind, 5, 9);

        fusionUnionFind(unionFind, 4, 6);

        fusionUnionFind(unionFind, 8, 7);

        fusionUnionFind(unionFind, 7, 9);

        fusionUnionFind(unionFind, 6, 8);

        printClassUnionFind(unionFind,3);
        printAllClassesUnionFind(unionFind);

        makeGraphvizGraph(unionFind, "graph");
        freeUnionFind(unionFind);
    }

    return 0;
}

