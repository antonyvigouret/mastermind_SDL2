#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "master.h"




int main(int argc, char *argv[]){


    int gagner = 0;
    int i = 0;
    int solution[NB_COLONNES];
    int plateau[NB_LIGNES][6];
    int proposition[NB_COLONNES];
    initialiser_solution(solution);
    initialiser_plateau(plateau);
    //printf("couleurs de 1 à %d\n\n", NB_COULEURS);

    printf("\n\n");

    while (!gagner && (i < 10)){
        printf("tour %d\n", i);
        saisir_proposition(proposition);
        actualiser_plateau(plateau, proposition, solution, i);

        // gagner ?
        if (compare(proposition, solution)){
            gagner = 1;
            printf("vous avez gagnez !\n");
        }
        i++;
    }



    return EXIT_SUCCESS;
}