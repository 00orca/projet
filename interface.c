#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
void logErreur() 
{
	SDL_Log("Erreur: %s.", SDL_GetError());
	SDL_ClearError();
}

bool init(SDL_Window** win, SDL_Renderer** ren,char *titre)
{
	/* vérifier les parametres */
	if (win == NULL || ren == NULL)
	{
		return FALSE;
	}

	/* init SDL2 */
	if (0 != SDL_Init(SDL_INIT_EVERYTHING))
	{
		logErreur();
		return FALSE;
	}

	/* creation de fenetre */
	SDL_Window* window = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		logErreur();
		SDL_Quit();
		return FALSE;
	}

	/* creer Renderer */
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

		if (renderer == NULL)
		{
			logErreur();
			SDL_DestroyWindow(window);
			SDL_Quit();
			return FALSE;
		}
	}
	*win = window;
	*ren = renderer;
	return TRUE;
}

void draw(SDL_Renderer* renderer)
{
	/* Vérifier les couleur qu'on va utiliser */
	if (0 != SDL_SetRenderDrawColor(renderer, 0xbb, 0xbb, 0xbb, 0xff))logErreur();
	if (0 != SDL_RenderClear(renderer))logErreur();
	if (0 != SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xbb))logErreur();

	int longeur = SCREEN_WIDTH - 40;
	int part = longeur / 15;
	if (0 != SDL_RenderDrawLine(renderer, part, part, part, longeur))logErreur();
	if (0 != SDL_RenderDrawLine(renderer, longeur, part, longeur, longeur))logErreur();
	
	for (int y = part; y <= longeur; y +=( longeur- part)/5)
	{
		if (0 != SDL_RenderDrawLine(renderer, part, y, longeur, y))
			logErreur();
	}

	SDL_RenderPresent(renderer);
}

SDL_Texture* load_image(char * filename, SDL_Renderer *renderer){
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

SDL_Texture* RenderText(char* message, char* fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
	TTF_Font *font = NULL;
	font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL)
		fprintf(stderr, "erreur chargement font\n");

	SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	return texture;
}

