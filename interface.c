#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

SDL_Surface *gpScreen;
SDL_Renderer *renderer;
TTF_Font *font;
FILE *fp2;
SDL_Color r = {255,100,0,255};
SDL_Color o = {255,165,0,255};
SDL_Color b = {255,255,255,255};

void loadImage(image_t image[Z],SDL_Renderer *renderer){
	fp2=fopen ("images/lien_image.txt","r");
	for(int i=0;i<Z && !feof(fp2);i++){

		fscanf(fp2, "%s", image[i].loc_image);
		image[i].texture=IMG_LoadTexture(renderer,image[i].loc_image);
	}

	fclose(fp2);
}

void afficher_img(int x,int y,int h,int w,char img[50],image_t image[Z],SDL_Renderer *renderer,float coefZoom){
	SDL_Rect imgDestRect;
	imgDestRect.x = x;
	imgDestRect.y = y;
	imgDestRect.w=w*coefZoom;
	imgDestRect.h=h*coefZoom;
	for(int i=0;i<Z;i++){
		if(!strcmp(image[i].loc_image,img)){
			SDL_RenderCopy(renderer, image[i].texture, NULL, &imgDestRect);
			return;
		}
	}
}

void AfficherText(char* message, char* fontFile, SDL_Color color, int fontSize,SDL_Renderer *renderer,int x,int y)
{
	SDL_Rect txtDestRect;
	font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL)
		fprintf(stderr, "erreur chargement font\n");

	SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	txtDestRect.x = x;
	txtDestRect.y = y;
	SDL_QueryTexture(texture,NULL,NULL,&txtDestRect.w,&txtDestRect.h);
	SDL_RenderCopy(renderer, texture, NULL, &txtDestRect);

	SDL_DestroyTexture(texture);
}

int draw_menu(SDL_Renderer *renderer,SDL_Window* pWindow){
	gpScreen = SDL_GetWindowSurface(pWindow);
	int longeur = gpScreen->h/5;
	int fonsize = longeur/2;
	int yy = fonsize/2;
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, 0, longeur, gpScreen->w, longeur);
	SDL_RenderDrawLine(renderer, 0, longeur*2, gpScreen->w, longeur*2);
	SDL_RenderDrawLine(renderer, 0, longeur*3, gpScreen->w, longeur*3);
	SDL_RenderDrawLine(renderer, 0, longeur*4, gpScreen->w, longeur*4);

	AfficherText("TACTICS ARENA", "arial.ttf",r,fonsize,renderer,fonsize*4,yy);
	AfficherText("HUMAIN VS HUMAIN", "arial.ttf",o,fonsize-10,renderer,fonsize*4,yy*5);
	AfficherText("HUMAIN vs ORDINATEUR", "arial.ttf",o,fonsize-10,renderer,fonsize*3,yy*9);
	AfficherText("ABOUT US", "arial.ttf",o,fonsize-10,renderer,fonsize*6,yy*13);
	AfficherText("QUIT", "arial.ttf",o,fonsize-10,renderer,fonsize*7,yy*17);

  SDL_RenderPresent(renderer);
	return longeur;
}

void about(SDL_Renderer *renderer,SDL_Window* pWindow){
	gpScreen = SDL_GetWindowSurface(pWindow);
	int longeur = gpScreen->h/5;
	int fonsize = longeur/4;
	int yy = fonsize/2;
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

	AfficherText("L2 INFO Conduite de Projet", "arial.ttf",r,fonsize,renderer,fonsize*4,yy);
	AfficherText("Tactics Arena", "arial.ttf",r,fonsize,renderer,fonsize*5,yy*4);
	AfficherText("LEPOITTEVIN ELIOT", "arial.ttf",o,fonsize-15,renderer,fonsize*5,yy*8);
	AfficherText("LIBAN WILLHEM", "arial.ttf",o,fonsize-15,renderer,fonsize*5,yy*10);
	AfficherText("LIU YICHENG", "arial.ttf",o,fonsize-15,renderer,fonsize*5,yy*12);
	AfficherText("BACK", "arial.ttf",b,15,renderer,gpScreen->w - 60,gpScreen->h - 30);
  SDL_RenderPresent(renderer);
}
