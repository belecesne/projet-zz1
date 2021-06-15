#include "../headers/tas.h"

int main() {
    int * tab = malloc(10 * sizeof(int));
    tab[0] = 10;
    tab[1] = 9;
    tab[2] = 8;
    tab[3] = 7;
    tab[4] = 6;
    tab[5] = 5;
    tab[6] = 4;
    tab[7] = 3;
    tab[8] = 2;
    tab[9] = 1;
    for(int i = 0; i < 10; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    tri_tas(tab, 10);
    for(int i = 0; i < 10; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}