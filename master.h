#ifndef master_h
#define master_h
#include <SDL2/SDL.h>

/* DECLARATION DES CONSTANTES SYMBOLIQUES */

#define NB_COLONNES 4
#define NB_LIGNES 10
#define NB_COULEURS 4


/* DECLARATION DES TYPES PERSONNELS */
// et de leur typedef si besoin

typedef struct {
    int bienp;
    int malp;
} combinaison;

typedef enum {
    RIEN,
    ROUGE,
    VERT,
    CYAN,
    BLEU
}Couleur;

/* DECLARATIONS DES METHODES */

void initialiser_solution(int sol[]);
void initialiser_plateau(int plateau[][6]);
combinaison compiler_proposition(int proposition[], int solution[]);
void actualiser_plateau(int plateau[][6], int proposition[],int solution[], int tour);
void saisir_proposition(int proposition[]);
int compare(int proposition[], int solution[]);
void viderBuffer();

// DECLARATION METHODES SDL
void ExitWithError(char *message);
void Dessiner_Ligne(SDL_Renderer *renderer, int pos_y, Couleur c[4]);
void Dessiner_Rectangle(SDL_Renderer *renderer, int pos_x, int pos_y, Couleur couleur);
void Init_Proposition(Couleur c[4]);
void Ajout_Couleur(Couleur c[4], Couleur couleur);

#endif