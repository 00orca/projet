#include <stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define N 10
#define M 10


int main(int argc, char** argv)
{
    //Le pointeur vers la fenetre
	SDL_Window* pWindow = NULL;
	//Le pointeur vers la surface incluse dans la fenetre
    //SDL_Surface *texte=NULL, *image=NULL;
	SDL_Renderer *renderer=NULL;


	//SDL_Rect txtDestRect;
  SDL_Rect  imgDestRect;
	// Le pointeur vers notre police
//	TTF_Font *police = NULL;
	// Une variable de couleur noire
	//SDL_Color couleurNoire = {0, 0, 0};


    /* Initialisation simple */
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
	pWindow = SDL_CreateWindow("Hello World SDL2",SDL_WINDOWPOS_UNDEFINED,
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

/*
	if( (police = TTF_OpenFont("police/arial.ttf", 20)) == NULL){
		fprintf(stderr, "erreur chargement font\n");
		exit(EXIT_FAILURE);
	}
*/
//DU TEXTE
	/*texte = TTF_RenderUTF8_Blended(police, "Vive la programmation !", couleurNoire);
	if(!texte){
		fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
	if(!texte_tex){
		fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
  */
	//SDL_FreeSurface(texte); /* on a la texture, plus besoin du texte */
	/* Position ou sera mis le texte dans la fenêtre */
  /*
    txtDestRect.x = txtDestRect.y = 10;
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
  */

	// CREATION TEXTURE CASE DE BASE
	SDL_Surface* image2 = IMG_Load("images/case_normal.png");
	SDL_Texture* image_case_normale = SDL_CreateTextureFromSurface(renderer,image2);
	SDL_FreeSurface(image2);



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

							//AFFICHAGE DE LA CARTE
							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
										if(compteur==0){
											SDL_QueryTexture(image_case_normale, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
										}
										SDL_RenderCopy(renderer, image_case_normale, NULL, &imgDestRect);
									}


								}


							SDL_RenderPresent(renderer);

							break;
						}
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
