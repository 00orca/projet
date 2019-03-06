#include "interface.h"

int main() 
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	if (!init(&window, &renderer,"test"))exit(1);

	draw(renderer);

	SDL_Rect rect = { 0,0,10,10 };
	Uint8 r = 0xff, g = 0xff, b = 0xff;
	SDL_Event event;
	while (1) {
		SDL_PollEvent(&event);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);
		if (event.type == SDL_MOUSEMOTION)
		{
			rect.x = event.motion.x;
			rect.y = event.motion.y;
		}
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
