#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "master.h"

#define WINDOW_W 474
#define WINDOW_H 600

int main(int argc, char **argv){

	 int solution[NB_COLONNES];// = {1, 2, 3 ,1};
	 initialiser_solution(solution);
	 for (int i = 0; i < 4; i++) printf("%d ", solution[i]);

   Couleur proposition[4];
   Init_Proposition(proposition);

   SDL_Window *window = NULL;
   SDL_Renderer *renderer = NULL;
   if (SDL_Init(SDL_INIT_VIDEO) < 0){
      ExitWithError("Initialisation SDL");
   }

   //Création fenêtre
   window = SDL_CreateWindow("Mastermind 1.0", SDL_WINDOWPOS_CENTERED,
   SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);

   if (window == NULL){
      ExitWithError("Creation fenetre");
   }

   //Création rendu
   renderer = SDL_CreateRenderer(window, -1, 0);

   if (renderer == NULL){
      SDL_DestroyWindow(window);
      ExitWithError("Creation rendu");
   }

   SDL_Surface *surface = NULL;
   SDL_Texture *texture = NULL;

   surface = SDL_LoadBMP("texture.bmp");

   if (surface == NULL){
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      ExitWithError("chargement image");
   }

   texture = SDL_CreateTextureFromSurface(renderer, surface);
   if (texture == NULL){
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      ExitWithError("creation texture");
   }

   SDL_Rect rectangle;


   if (SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0){
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      ExitWithError("charger la texture");      
   }

   rectangle.x = (WINDOW_W - rectangle.w) / 2;
   rectangle.y = (WINDOW_H - rectangle.h) / 2;

   if (SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0){
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      ExitWithError("afficher la texture");     
   }

   // 5 BOUTONS
   Couleur init[4] = {ROUGE, VERT, CYAN, BLEU};
   Dessiner_Ligne(renderer, WINDOW_H-70, init);
   SDL_Rect rect = {350, WINDOW_H-70, 70, 50};
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
   SDL_RenderFillRect(renderer, &rect);

   SDL_RenderPresent(renderer);

   SDL_bool program_launched = SDL_TRUE;

	 int i = 0;
	 int j = 0;
	 

   while (program_launched && (i < 10)){
      SDL_Event event;
      
      
      while (SDL_PollEvent(&event)){

         switch (event.type){
            case SDL_QUIT:
               program_launched = SDL_FALSE;
               break;
            case SDL_MOUSEBUTTONDOWN:
               switch (event.button.button){
                  //clique gauche
                  case SDL_BUTTON_LEFT:
                     ;
                     int x;
                     x = event.motion.x;
                     int y;
                     y = event.motion.y;
                     //on vérifie la position de la souris par rapport a la barre des boutons
                     //printf("%d %d \n",x , y);
                     if ((y <= WINDOW_H-20) && (x <= 420) && (x >= 70) && (y >= WINDOW_H-70)){
                        //printf("ok\n");
                        switch ((x-70) / 70){
                           case 0:
                              if (j<4){
																Ajout_Couleur(proposition, ROUGE);
																Dessiner_Rectangle(renderer, 70+j*70, WINDOW_H -125 -i*55, ROUGE);
																SDL_RenderPresent(renderer);
																j++;
															}
                              break;
                           case 1:
                              if (j<4){
																Ajout_Couleur(proposition, VERT);
																Dessiner_Rectangle(renderer, 70+j*70, WINDOW_H -125 -i*55, VERT);
																SDL_RenderPresent(renderer);
																j++;
															}
                              break;
                           case 2:
                              if (j<4){
																Ajout_Couleur(proposition, CYAN);
																Dessiner_Rectangle(renderer, 70+j*70, WINDOW_H -125 -i*55, CYAN);
																SDL_RenderPresent(renderer);
																j++;
															}
                              break;
                           case 3:
                              if (j<4) {
																Ajout_Couleur(proposition, BLEU);
																Dessiner_Rectangle(renderer, 70+j*70, WINDOW_H -125 -i*55, BLEU);
																SDL_RenderPresent(renderer);
																j++;
															}
                              break;
                           case 4:
                              //Dessiner_Ligne(renderer, WINDOW_H -70 -i*55, proposition);
															if (j == 4){
																i++;
																j = 0;
																printf("validation\n");
																combinaison resultat = compiler_proposition(proposition, solution);
																printf("b : %d , m : %d\n", resultat.bienp, resultat.malp);
																if (resultat.bienp > 0){
																	for (int k = 0; k < resultat.bienp; k++){
																		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
																		SDL_Rect rect = {370 + 20*k, WINDOW_H -60 -i*55, 10, 10} ;
																		SDL_RenderFillRect(renderer, &rect);
																	}
																}
																if (resultat.malp > 0){
																	for (int k = 0; k < resultat.malp; k++){ 
																		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
																		SDL_Rect rect = {370 + 20*k, WINDOW_H -40 -i*55, 10, 10};
																		SDL_RenderFillRect(renderer, &rect);
																	}
																}
																if (compare(proposition, solution)){
																	program_launched = SDL_FALSE;
																	printf("vous avez gagnez !\n");
																}
																SDL_RenderPresent(renderer);															
																Init_Proposition(proposition);
															}															
                              break;
                           default:
                              printf("default\n");
                              break;   
                              
                        }
                     }
                     //printf("%d %d\n",event.motion.x, event.motion.y);
                     //Couleur c[4] = { BLEU, ROUGE, VERT, CYAN};
                     //Dessiner_Ligne(renderer, event.motion.y, c);
                     //SDL_RenderPresent(renderer);
                     break;
                  case SDL_BUTTON_RIGHT:
										 for (int i = 0; i < 4; i++) printf("%d\n", proposition[i]);
                     Init_Proposition(proposition);
                     j = 0;
                     
                  default:
                     continue;
               }
            default:
               continue;

         }
      }
   }



   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   SDL_Quit();
   return EXIT_SUCCESS;
}

