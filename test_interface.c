#include "interface.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	SDL_Window* window = NULL;
	if (!init())printf("erreur\n");
	create_fenetre("tictac arena", window);

	SDL_Texture *background = NULL;
	background = load_image("arena.bmp");

	SDL_RenderClear(renderer);
	int bW, bH;
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
	apply_surface(0, 0, background, renderer);
	ApplySurface(bW, 0, background, renderer);
	ApplySurface(0, bH, background, renderer);
	ApplySurface(bW, bH, background, renderer);

	SDL_RenderPresent(renderer);
	SDL_Delay(2000);

	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}