#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "master.h"

// fonction qui initialise une solution (4 couleurs)
void initialiser_solution(int sol[]) {
   srand(time(0));
   for (int i=0; i<NB_COLONNES; i++){
       sol[i]=(rand()%NB_COULEURS)+1;
   }
}

// fonction qui initialise un plateau vierge
void initialiser_plateau(int plateau[][6]){
   for (int i=0; i<NB_LIGNES; i++){
       for (int j=0; j<6; j++){
           plateau[i][j]=0;
       }
   }
}

// fonction modifie et affiche le plateau en entier
void actualiser_plateau(int plateau[][6], int proposition[], int solution[], int tour){
    // actualisation
    for (int i = 0; i < 4; i++) plateau[tour][i] = proposition[i];
    combinaison c=compiler_proposition(proposition, solution);
    plateau[tour][4] = c.bienp;
    plateau[tour][5] = c.malp;

    // affichage
    printf("=============b=m==\n");
    for (int i = 0; i < NB_LIGNES; i++){
        printf("| ");
        for (int j = 0; j < 4; j++){
            printf("\033[%dm  ", plateau[i][j]+40);
        }
        printf("\033[40m|| ");
        for (int j = 4; j < 6; j++){
            printf("%d ", plateau[i][j]);
        }
        printf(" |\n");
    }
    printf("===================\n");

}

// fonction qui compare la proposition et le solution
int compare(int proposition[], int solution[]){
    int tmp = 0;
    for (int i = 0; i<4; i++){
        if ((proposition[i]==solution[i])) tmp++;
    }
    int win;
    win = (tmp == 4) ? 1 : 0;
    return win;
}

// fonction saisie la proposition du joueur
void saisir_proposition(int proposition[]){
    int c;
    printf("veuillez saisir 4 couleurs (\033[41m1\033[40m \033[42m2\033[40m \033[43m3\033[40m \033[44m4\033[40m)\n");
    for (int i = 0; i < NB_COLONNES; i++){
        c = getchar();
        char c2 = (char)c;
        proposition[i] = atoi(&c2);
    }
    viderBuffer();
}

// calcul les couleurs bien/mal placées
combinaison compiler_proposition(int proposition[], int solution[]) {
	combinaison resultat;
    resultat.bienp = 0;
    resultat.malp = 0;

    int soltmp[4];
    for (int i = 0; i < 4; i++) soltmp[i] = solution[i];

    for (int i=0; i<NB_COLONNES; i++){
        if (proposition[i] == soltmp[i]){
             resultat.bienp++;
             soltmp[i] = 0;
        }
    }
    for (int i=0; i<NB_COLONNES; i++){
        if  (soltmp[i]){
            for (int j=0; j<NB_COLONNES; j++){
                if (proposition[i] == soltmp[j]) {
                    soltmp[j] = 5;
                    resultat.malp++;
                    break;
                }
            }
        }
    }
    return resultat;
} 

// vidage du buffer
void viderBuffer(){
    char c = 0;
    while (c != '\n' && c != EOF) c=getchar();
}



/* -------------------------------------------------
                    FONCTION SDL                    */

void ExitWithError(char *message){
    SDL_Log("ERREUR : %s -> %s",message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


void Dessiner_Ligne(SDL_Renderer *renderer, int pos_y, Couleur c[4]){
    if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) != 0){
        ExitWithError("changer couleur"); 
    }
    for (int i = 0; i < 4; i++){
        Dessiner_Rectangle(renderer, 70+70*i, pos_y, c[i]);
    }
}
;
void Dessiner_Rectangle(SDL_Renderer *renderer, int pos_x, int pos_y, Couleur couleur){
    switch (couleur){
        case ROUGE:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            break;
        case VERT:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            break;
        case CYAN:
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            break;
        case BLEU:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            break;
        default:
            break;
    }
    SDL_Rect rectangle = {pos_x, pos_y, 70, 50};
    SDL_RenderFillRect(renderer, &rectangle);
}

void Init_Proposition(Couleur c[4]){
    for (int i = 0; i < 4; i++) c[i] = RIEN;
}

void Ajout_Couleur(Couleur c[4], Couleur couleur){
    for (int i = 0; i < 4; i++){
        if (c[i] == RIEN) c[i] = couleur;
    }
}