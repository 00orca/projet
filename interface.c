#include "interface.h"
#include <stdio.h>
#include <stdlib.h>

SDL_Surface *gpScreen;
SDL_Renderer *renderer;
TTF_Font *font;

bool init()
{
	/*init SDL*/
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return FALSE;
	}

	/* Initialisation TTF */
	if (TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		return FALSE;
	}
	return TRUE;
}

bool create_fenetre(char* titre, SDL_Window* window)
{
	window = SDL_CreateWindow(
		titre,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,                               // width
		SCREEN_HEIGHT,                              // height
		SDL_WINDOW_SHOWN                  // flags - see below
	);
	if (window == NULL) {
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		fprintf(stderr, "Erreur à la creation du renderer\n");
		return FALSE;
	}
	gpScreen = SDL_GetWindowSurface(window);
	return TRUE;
}

SDL_Texture* load_image(char * filename){
	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;

	image = IMG_Load(filename);
	if (image != NULL) {
		texture = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);
	}
	else
		fprintf(stderr, "Erreur au chargement de l'image : %s\n", SDL_GetError());
	return texture;
}

void apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend) {
	SDL_Rect indice;
	indice.x = x;
	indice.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &indice.w, &indice.h);

	SDL_RenderCopy(rend, tex, NULL, &indice);
}

SDL_Texture* RenderText(char* message, char* fontFile, SDL_Color color, int fontSize)
{
	font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL)
		fprintf(stderr, "erreur chargement font\n");

	SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	return texture;
}

