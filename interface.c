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
	int y = fonsize/2;
	int x = gpScreen->w/10;
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, 0, longeur, gpScreen->w, longeur);
	SDL_RenderDrawLine(renderer, 0, longeur*2, gpScreen->w, longeur*2);
	SDL_RenderDrawLine(renderer, 0, longeur*3, gpScreen->w, longeur*3);
	SDL_RenderDrawLine(renderer, 0, longeur*4, gpScreen->w, longeur*4);

	AfficherText("TACTICS ARENA", "arial.ttf",r,fonsize,renderer,x*2.5,y);
	AfficherText("NEW GAME", "arial.ttf",o,fonsize-10,renderer,x*3,y*5);
	AfficherText("LOAD GAME", "arial.ttf",o,fonsize-10,renderer,x*3,y*9);
	AfficherText("ABOUT US", "arial.ttf",o,fonsize-10,renderer,x*3,y*13);
	AfficherText("QUIT", "arial.ttf",o,fonsize-10,renderer,x*3,y*17);

  SDL_RenderPresent(renderer);
	return longeur;
}

void about(SDL_Renderer *renderer,SDL_Window* pWindow){
	gpScreen = SDL_GetWindowSurface(pWindow);
	int longeur = gpScreen->h/5;
	int fonsize = longeur/4;
	int y = fonsize/2;
	int x = gpScreen->w/10;
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

	AfficherText("L2 INFO Conduite de Projet", "arial.ttf",r,fonsize,renderer,x*3,y);
	AfficherText("Tactics Arena", "arial.ttf",r,fonsize,renderer,x*3,y*4);
	AfficherText("LEPOITTEVIN ELIOT", "arial.ttf",o,fonsize-15,renderer,x*3,y*8);
	AfficherText("LIBAN WILLHEM", "arial.ttf",o,fonsize-15,renderer,x*3,y*10);
	AfficherText("LIU YICHENG", "arial.ttf",o,fonsize-15,renderer,x*3,y*12);
	AfficherText("BACK", "arial.ttf",b,15,renderer,gpScreen->w - 60,gpScreen->h - 30);
  SDL_RenderPresent(renderer);
}

void ingame_menu(SDL_Renderer *renderer,SDL_Window* pWindow){
	gpScreen = SDL_GetWindowSurface(pWindow);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect menu;
    menu.x = gpScreen->w - 260;
    menu.y = gpScreen->h - 330;
    menu.w = 200;
    menu.h = 300;
    SDL_RenderFillRect(renderer,&menu);

		int n = 300/4;
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
	  SDL_RenderDrawLine(renderer, menu.x, menu.y+n, menu.x+200, menu.y+n);
		SDL_RenderDrawLine(renderer, menu.x, menu.y+n*2, menu.x+200, menu.y+n*2);
		SDL_RenderDrawLine(renderer, menu.x, menu.y+n*3, menu.x+200, menu.y+n*3);

		AfficherText("Reculer", "arial.ttf",o,menu.h/10,renderer,menu.x+20,menu.y+menu.h/13);
		AfficherText("Save Game", "arial.ttf",o,menu.h/10,renderer,menu.x+20,menu.y+n+menu.h/13);
		AfficherText("Help", "arial.ttf",o,menu.h/10,renderer,menu.x+20,menu.y+n*2+menu.h/13);
		AfficherText("Quit", "arial.ttf",o,menu.h/10,renderer,menu.x+20,menu.y+n*3+menu.h/13);
		SDL_RenderPresent(renderer);
}

void help(SDL_Renderer *renderer,SDL_Window* pWindow){
	gpScreen = SDL_GetWindowSurface(pWindow);
	int longeur = gpScreen->h/5;
	int fonsize = longeur/4;
	int y = fonsize/2;
	int x = gpScreen->w/10;
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

	AfficherText("Comment jouer TACTICS ARENA?", "arial.ttf",r,fonsize,renderer,x*3,y);
	AfficherText(".......................", "arial.ttf",r,fonsize,renderer,x*3,y*4);
	AfficherText("BACK", "arial.ttf",b,15,renderer,gpScreen->w - 60,gpScreen->h - 30);
  SDL_RenderPresent(renderer);
}

void mod_menu(SDL_Renderer *renderer,SDL_Window* pWindow,int nb_j,int nb_o,int taille,int nb_unit){
	char variable[50];
	gpScreen = SDL_GetWindowSurface(pWindow);
	int longeur = gpScreen->h/5;
	int fonsize = longeur/2;
	int y = fonsize/2;
	int x = gpScreen->w/10;
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, 0, longeur, gpScreen->w, longeur);
	SDL_RenderDrawLine(renderer, 0, longeur*2, gpScreen->w, longeur*2);
	SDL_RenderDrawLine(renderer, 0, longeur*3, gpScreen->w, longeur*3);
	SDL_RenderDrawLine(renderer, 0, longeur*4, gpScreen->w, longeur*4);

	AfficherText("Nombre de Joueur: ", "arial.ttf",o,fonsize,renderer,0,y);
	AfficherText("+", "arial.ttf",o,fonsize,renderer,gpScreen->w - x*2,y);
	AfficherText("-", "arial.ttf",o,fonsize,renderer,gpScreen->w - x,y);
	sprintf(variable, "%d",  nb_j);
	AfficherText(variable, "arial.ttf",o,fonsize,renderer,gpScreen->w - x*4,y);

	AfficherText("Nombre d'Ordinateur:", "arial.ttf",o,fonsize,renderer,0,y*5);
	AfficherText("+", "arial.ttf",o,fonsize,renderer,gpScreen->w - x*2,y*5);
	AfficherText("-", "arial.ttf",o,fonsize,renderer,gpScreen->w - x,y*5);
	sprintf(variable, "%d",  nb_o);
	AfficherText(variable, "arial.ttf",o,fonsize,renderer,gpScreen->w - x*4,y*5);

	AfficherText("Taille de la grille:", "arial.ttf",o,fonsize,renderer,0,y*9);
	AfficherText("+", "arial.ttf",o,fonsize,renderer,gpScreen->w - x*2,y*9);
	AfficherText("-", "arial.ttf",o,fonsize,renderer,gpScreen->w - x,y*9);
	sprintf(variable, "%d",  taille);
	AfficherText(variable, "arial.ttf",o,fonsize,renderer,gpScreen->w - x*4,y*9);

	AfficherText("Nombre de Unit:", "arial.ttf",o,fonsize,renderer,0,y*13);
	AfficherText("+", "arial.ttf",o,fonsize,renderer,gpScreen->w - x*2,y*13);
	AfficherText("-", "arial.ttf",o,fonsize,renderer,gpScreen->w - x,y*13);
	sprintf(variable, "%d",  nb_unit);
	AfficherText(variable, "arial.ttf",o,fonsize,renderer,gpScreen->w - x*4,y*13);

	AfficherText("Suivant", "arial.ttf",r,fonsize,renderer,x*4,y*17);

  SDL_RenderPresent(renderer);
}
