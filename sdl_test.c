#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define N 7
#define M 7

//=======STRUCT========//

typedef enum {
    soldat, archer,cavalier
}classe_t;


typedef struct piece_s{
    char * nom_classe;
    int pdv; //point de vie
    int puissance;
    int armure;
    int block; //pourcentage de chance de bloquer
    int portee; //portée de l'attaque
    int deplacement; //nombre de case de mouvement
}piece_t;


typedef struct case_s{
	int type;
	SDL_Texture *type_case;
	int climat;
	piece_t *piece;
}case_t;





//=====================================MAIN=============================//

int main(int argc, char** argv)
{
	SDL_Window* pWindow = NULL;
	SDL_Renderer *renderer=NULL;
  SDL_Rect  imgDestRect;

	int preset,alea,var1;
	case_t terrain[N][M];
	srand(time(NULL));
	FILE * fp;





    /* Initialisation SDL*/
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Jeanne Oscour",SDL_WINDOWPOS_UNDEFINED,
												  SDL_WINDOWPOS_UNDEFINED,
												  1200,
												  800,
												  SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

	if(!pWindow){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}

//===================================TEXTURES==========================================//

	// CREATION TEXTURE CASE DE BASE  TYPE=1
	SDL_Surface* image = IMG_Load("images/case_normal.png");
	SDL_Texture* image_case_normale = SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);
	// CREATION TEXTURE CASE D'eau  TYPE=5
	image = IMG_Load("images/case_eau.png");
	SDL_Texture* image_case_eau = SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);
	// CREATION TEXTURE CASE DE foret TYPE=6
	image = IMG_Load("images/case_foret.png");
	SDL_Texture* image_case_foret = SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);
	// CREATION TEXTURE CASE DE montagne  TYPE=7
	image = IMG_Load("images/case_montagne.png");
	SDL_Texture* image_case_montagne = SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);
	// CREATION TEXTURE CASE DE BASE COIN  TYPE=2
	image = IMG_Load("images/case_normal_coin.png");
	SDL_Texture* image_case_coin = SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);
	// CREATION TEXTURE de bordure gauche  TYPE=3
	image = IMG_Load("images/case_normal_bordure_gauche.png");
	SDL_Texture* image_case_normal_bordure_gauche = SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);
	// CREATION TEXTURE de bordure droite  TYPE=4
	image = IMG_Load("images/case_normal_bordure_droite.png");
	SDL_Texture* image_case_normal_bordure_droite = SDL_CreateTextureFromSurface(renderer,image);
	SDL_FreeSurface(image);

//==================================INITIALISATION GRILLE============================//

	printf("1 POUR CARTE ALEATOIRE, AUTRE CHIFFRE POUR UNE DES CARTES PRESET : ");
	scanf("%d",&preset);


	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){

			if(preset==1){			//======aleatoire=======//

				if(i==0 && j==0){
					terrain[j][i].type=2;
				}
				else if(i==0 && j>0){
					terrain[j][i].type=4;
				}
				else if(i>0 && j==0){
					terrain[j][i].type=3;
				}
				else{
					alea=rand()%6;
					if(alea==0){
						terrain[j][i].type=5;
					}
					else if(alea==1){
						terrain[j][i].type=4;
					}
					else if(alea==2){
						terrain[j][i].type=6;
					}
					else if(alea>=3){
						terrain[j][i].type=1;
					}
				}

			}else{						//=====preset de carte chargé par fichiers=====//
				fp = fopen ("fichiers/preset1.txt", "w");
				fscanf(fp, "%d ", &var1);
				terrain[j][i].type=var1;

			}

		}

	}
	if(preset!=1){
		fclose(fp);
	}



	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			if(terrain[j][i].type==1){
				terrain[j][i].type_case=&(image_case_normale);
			}
			else if(terrain[j][i].type==2){
				terrain[j][i].type_case=&(image_case_coin);
			}
			else if(terrain[j][i].type==3){
				terrain[j][i].type_case=&(image_case_normal_bordure_gauche);
			}
			else if(terrain[j][i].type==4){
				terrain[j][i].type_case=&(image_case_normal_bordure_gauche);
			}
			else if(terrain[j][i].type==5){
				terrain[j][i].type_case=&(image_case_eau);
			}
			else if(terrain[j][i].type==6){
				terrain[j][i].type_case=&(image_case_foret);
			}
			else if(terrain[j][i].type==7){
				terrain[j][i].type_case=&(image_case_montagne);
			}
			terrain[j][i].climat=0;
			terrain[j][i].piece=NULL;

		}
	}




//========================================FENETRE=====================================//

	if( pWindow )
	{
		int running = 1;
		while(running) {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: running = 0;
					break;
					case SDL_WINDOWEVENT:
						switch(e.window.event){
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SHOWN:

							//======================================BOUCLE D'AFFICHAGE=========================================//
							SDL_SetRenderDrawColor(renderer, 125, 125, 125, 125);
							SDL_RenderClear(renderer);
							(imgDestRect.w)=50;
							(imgDestRect.h)=50;
							int bordure=20;
							int indice,indice2,indice3,indice4;
							int compteur,compteur2;

								for( indice3 = bordure + (imgDestRect.h) * N , compteur=0 , indice4=bordure + (imgDestRect.w) * N /2 ; compteur<M ; indice3-=(imgDestRect.h)/2.3, indice4-= (imgDestRect.w)/3, compteur++){
									for(compteur2=0 , indice= indice3 , indice2 = indice4 ; compteur2<N ; compteur2++, indice-=(imgDestRect.h)/2.3, indice2+= (imgDestRect.w)/3){

										imgDestRect.x = indice2;
										imgDestRect.y = indice;
										//fprintf(stderr,"indice = %d , indice 2 = %d , indice3 = %d , indice 4 = %d \n",indice,indice2,indice3,indice4);
										SDL_QueryTexture(terrain[compteur2][compteur].type_case, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
										//SDL_RenderCopy(renderer, terrain[compteur2][compteur].type_case, NULL, &imgDestRect);
										if(terrain[compteur2][compteur].piece){


										}
										if(terrain[compteur2][compteur].climat != 0){


										}
										//autre affichages :

										//

									}
								}

							SDL_RenderPresent(renderer);

							break;
						}
							//===================================DEROULEMENT DU JEU==========================================//
							/*

							0) choix mode de jeu,premiere affichage au début du match juste avant avec carte de base et l'interface puis selection des unitées et mise a jours de la matrice
							puis affichage de nouveau avec les pieces affichées

							1)apparition de potentiel élements climatiques et changement des valeur dans la matrice pour les afficher dans la boucle d'affichage

							2)choix d'un perso ennemi a examiner ou d'un de ses perso pour déplacement ou attaque ennemi a porté + mise a jour des stats en fonction du terrain actuel
							 (mise a 1 d'une variable pour afficher dans la boucle d'affichage les cases de potentiel deplacement et attaques)

							 3)deplacement / combat (changement de place d'un personnage, calcule des dégats etc puis boucle d'affichage pour deplacer le perso, suprimmer les morts etc)
							 et verification de vitoire ou non pour afficher une message de victoire et retourner au menu

							 4)repetition des etapes 2 et 3 selon les points d'actions restants

							 5)changement d'une variable pour changement de joueur puis étapes de 1 a 5 de nouveau


							/*





					/*	for(int i=0; i<N; i++){
							for(int j=0; j<N; j++){
								printf("|%d|",terrain[N][M]);
							}
						}
						running=0;*/
					break;
				}
			}
		}
	} else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);

//	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
    SDL_Quit();

    return 0;
}
