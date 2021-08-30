#include "SDL.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define W 600
#define H 600
#define Rad 25
int main(int argc, char* argv[])
{
	srand(time(NULL));
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s("%s", SDL_GetError());
	}
	else
	{
		SDL_Window* window = NULL;
		window = SDL_CreateWindow(u8"Движущийся круг", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf_s("%s", SDL_GetError());
		}
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			
		    const int X= rand() % 200 + 200, Y = rand() % 200 + 200;
			double X1 = X, Y1 = X, angle = (rand() % 361) * 180 / 3.14;
			int color_R = 255, color_G = 255, color_B = 255;
			
			for (int i = 0;i <= Rad;i++)
				for (int t = 0;t <= 360;t++)
					SDL_RenderDrawPoint(renderer, X + i * cos(3.14 * t / 180), Y - i * sin(3.14 * t / 180));
			
			SDL_Event event;
			int quit = 0;
			
			while (!quit) {

				SDL_PollEvent(&event);
				if (event.type == SDL_QUIT) quit = 1;
				
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if(event.button.x!=X1)
							angle = atan((event.button.y-Y1)/(event.button.x-X1));
						if(event.button.x - X1 < 0)
							angle += 3.14;
					}		
					if (event.button.button == SDL_BUTTON_RIGHT)
					{
						if (event.button.x != X1)
							angle = atan((event.button.y - Y1) / (event.button.x - X1));
						if (event.button.x - X1 > 0)
							angle += 3.14;
					}
				}		
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
				SDL_RenderClear(renderer);
				SDL_SetRenderDrawColor(renderer, color_R, color_G, color_B, 0);

				for (int i = 0;i <= Rad;i++)
					for (int t = 0;t <= 360;t++)
						SDL_RenderDrawPoint(renderer, X1 + i * cos(3.14 * t / 180), Y1+ i * sin(3.14 * t / 180));
				
				if (X1 > Rad && X1 < W - Rad && Y1 > Rad && Y1 < H - Rad)
				{
					X1 +=2*cos(angle);  
					Y1 +=2*sin(angle);   
				}
				else
				{
					X1 = X;
					Y1 = Y;
					angle = (rand() % 361)*180/3.14;
					color_R = (color_R + rand() % 256) % 256;
					color_G = (color_G + rand() % 256) % 256;
					color_B = (color_B + rand() % 256) % 256;
				}
				SDL_RenderPresent(renderer);
			}
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
return 0;
}