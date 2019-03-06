#ifndef SDL_PROJET_H
#define SDL_PROJET_H

#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
/* booleen */
typedef int bool;
#define TRUE  1
#define FALSE 0

/* coleur */
#define WHITE 0xff
#define BLACK 0x00

//Resolution d'ecran
#define  SCREEN_WIDTH  640
#define  SCREEN_HEIGHT  640
#define  SCREEN_BPP  32

/*Declaration les fonctions*/
void logErreur();
bool init(SDL_Window** win, SDL_Renderer** ren, char *titre);
void draw(SDL_Renderer* renderer);

SDL_Texture* load_image(char * filename,SDL_Renderer *renderer);
void apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend);
#endif
