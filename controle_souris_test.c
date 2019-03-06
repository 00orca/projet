#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define  SCREEN_WIDTH  640
#define  SCREEN_HEIGHT  480
#define  SCREEN_BPP  32
int main(int argc, char* argv[])
{
	if (!init())exit(1);
	SDL_Window* win = SDL_CreateWindow("test", 
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED, 
										SCREEN_WIDTH, 
										SCREEN_HEIGHT, 
										SCREEN_BPP);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	SDL_Rect rect = { 0,0,10,10 };
	Uint8 r = 0xff, g = 0xff, b = 0xff;
	SDL_Event e;
	while (1)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, r, g, b, 0);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);

		if (0 == SDL_PollEvent(&e))
		{
			continue;
		}
		else if (e.type == SDL_QUIT)
		{
			break;
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			rect.x = e.motion.x;
			rect.y = e.motion.y;
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			r = e.button.button == SDL_BUTTON_LEFT ? 0xff : 0;
			g = e.button.button == SDL_BUTTON_MIDDLE ? 0xff : 0;
			b = e.button.button == SDL_BUTTON_RIGHT ? 0xff : 0;
		}
		else if (e.type == SDL_MOUSEWHEEL)
		{
			rect.w += e.wheel.y;
			rect.h += e.wheel.y;

		}
	}

	return 0;
}