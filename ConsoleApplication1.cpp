#include "SDL.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("%s", SDL_GetError());
	}
	else
	{
		SDL_Window* window = NULL;
		SDL_Surface* screenSurface = NULL;
		window = SDL_CreateWindow(u8"Окно", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
		if(window == NULL)
		{
			printf("%s", SDL_GetError());
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 127, 15));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(3000);
		SDL_FreeSurface(screenSurface);
		SDL_DestroyWindow(window);
		SDL_Quit();
		}
	}

	return 1;
}
