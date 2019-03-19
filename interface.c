#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

SDL_Surface *gpScreen;
SDL_Renderer *renderer;
TTF_Font *font;
FILE *fp2;

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

}
