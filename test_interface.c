#include "interface.h"

int main()
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	if (!init(&window, &renderer, "test"))exit(1);
	if (TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(1);
	}
	SDL_Texture *text;
	SDL_Rect txtDestRect;
	draw(renderer);

	text = RenderText("TICTAC ARENA", "arial.ttf", 0xbb, 50, renderer);
	txtDestRect.x = 135;
	txtDestRect.y =70;
	SDL_QueryTexture(text, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, text, NULL, &txtDestRect);

	text = RenderText("PLAYER VS PLAYER", "arial.ttf", 0xbb, 50, renderer);
	txtDestRect.x = 90;
	txtDestRect.y = 182;
	SDL_QueryTexture(text, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, text, NULL, &txtDestRect); 

	text = RenderText("PLAYER VS COM", "arial.ttf", 0xbb, 50, renderer);
	txtDestRect.x = 125;
	txtDestRect.y = 294;
	SDL_QueryTexture(text, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, text, NULL, &txtDestRect);

	text = RenderText("ABOUT US", "arial.ttf", 0xbb, 50, renderer);
	txtDestRect.x = 185;
	txtDestRect.y = 406;
	SDL_QueryTexture(text, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, text, NULL, &txtDestRect);
	SDL_RenderPresent(renderer);

	text = RenderText("QUIT GAME", "arial.ttf", 0xbb, 50, renderer);
	txtDestRect.x = 180;
	txtDestRect.y = 518;
	SDL_QueryTexture(text, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, text, NULL, &txtDestRect);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{

			int row = (event.button.y - 20) / 112;
			int column = (event.button.x - 20) / 600;

			if (row >= 0 && row <= 5 && column >= 0 && column <= 1)
			{
				if (row >= 1 && row < 2)printf("humain vs humain");
				if (row >= 2 && row < 3)printf("humain vs ordi");
				if (row >= 3 && row < 4)printf("about");
				if (row >= 4 && row < 5)break;
			}
		}
	}

	return TRUE;
}
