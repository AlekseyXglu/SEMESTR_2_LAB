//Лабораторная работа по примитивам
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#define W 600
#define H 800
using namespace std;

struct SNEG {
	int x;
	int y;
};

void Christmas_tree(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x96, 0x4b, 0x0, 0x0);
	SDL_Rect rect = { 280, 650, 40, 50 };
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	SDL_RenderDrawLine(renderer, 140, 650, 460, 650);
	int k = 80, m = 520;
	for (int i = 650; i > 100; i -= 10)
	{
		for (int j = 1;j <= 5;j++)
			SDL_RenderDrawLine(renderer, k + j, i + j, m - j, i - j);
		k += 4;
		m -= 4;
	}

	//Шарики
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	k = 100;
	m = 500;
	int r;
	for (int i = 620; i > 150; i -= 30)
	{
		r = rand() % (m - k + 1) + k;
		for (int p = 1; p <= 12; p++)
			for (int t = 0; t <= 360; t++)
				SDL_RenderDrawPoint(renderer, r + p * cos(3.14 * t / 180), i + p * sin(3.14 * t / 180));
		k += 13;
		m -= 13;
	}

	//Звезда
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 50);
	for (int p = 1; p <= 30; p++)
		for (int t = 0; t <= 360; t++)
			SDL_RenderDrawPoint(renderer, 300 + p * cos(3.14 * t / 180) * cos(3.14 * t / 180) * cos(3.14 * t / 180),
				100 + p * sin(3.14 * t / 180) * sin(3.14 * t / 180) * sin(3.14 * t / 180));
}

void first(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s("%s", SDL_GetError());
	}
	else
	{
		SDL_Window* window = NULL;
		window = SDL_CreateWindow(u8"Ёлка", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf_s("%s", SDL_GetError());
		}
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
		
			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
			SDL_RenderClear(renderer);

			Christmas_tree(renderer);

			SDL_RenderPresent(renderer);
			SDL_Delay(5000);
			SDL_DestroyRenderer(renderer);
		}
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}

void STARS(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 0, 50);
	int r;
	for (int i = 10; i <= 590; i += 5)
	{
		if (i <= 400) r = rand() % 760 + 20;
		else r = rand() % 580 + 300;

		for (int p = 1; p <= 4; p++)
			for (int t = 0; t <= 360; t++)
				SDL_RenderDrawPoint(renderer, i + p * cos(3.14 * t / 180) * cos(3.14 * t / 180) * cos(3.14 * t / 180),
					r + p * sin(3.14 * t / 180) * sin(3.14 * t / 180) * sin(3.14 * t / 180));
	}
}

void Luna(SDL_Renderer* renderer)
{
	for (int p = 1; p <= 60; p++)
		for (int t = 0; t <= 360; t++)
			SDL_RenderDrawPoint(renderer, 500 + p * cos(3.14 * t / 180), 150 + p * sin(3.14 * t / 180));
	SDL_SetRenderDrawColor(renderer, 0x0, 0x21, 0x37, 0);
	for (int p = 1; p <= 50; p++)
		for (int t = 0; t <= 360; t++)
			SDL_RenderDrawPoint(renderer, 550 + p * cos(3.14 * t / 180), 150 + p * sin(3.14 * t / 180));
}

void Kometa(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	int w = 255;
	for (int m = 5; m < 100; m++)
	{
		w -= 2;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 - w);
		for (int t = 0;t <= 360;t++)
			SDL_RenderDrawPoint(renderer, 3 * m + 23 * cos(3.14 * t / 180), m + 23 * sin(3.14 * t / 180));
	}
	for (int a = 0;a <= 27;a++)
		for (int t = 0; t <= 360; t++)
			SDL_RenderDrawPoint(renderer, 300 + a * cos(3.14 * t / 180), 100 + a * sin(3.14 * t / 180));
}

void two(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s("%s", SDL_GetError());
	}
	else
	{
		SDL_Window* window = NULL;
		window = SDL_CreateWindow(u8"Звёздное небо", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf_s("%s", SDL_GetError());
		}
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
			SDL_SetRenderDrawColor(renderer, 0x0, 0x21, 0x37, 0x0);
			SDL_RenderClear(renderer);
						
			STARS(renderer);
			Luna(renderer);
			Kometa(renderer);

			SDL_RenderPresent(renderer);
			SDL_Delay(5000);

			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}

double func(double a, double b, double x)
{
	return a * x * x + b;
}

void three(void)
{
	double x1, x2, a, b, ed;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s("%s", SDL_GetError());
	}
	else
	{
		SDL_Window* window = NULL;
		window = SDL_CreateWindow(u8"График", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf_s("%s", SDL_GetError());
		}
		else
		{
			printf("Введите параметр a:\n");
			scanf_s("%lf", &a);
			printf("Введите параметр b:\n");
			scanf_s("%lf", &b);

			do {
				printf("Нижняя граница:\n");
				scanf_s("%lf", &x1);
				printf("Верхняя граница:\n");
				scanf_s("%lf", &x2);
				if (x1 >= x2) printf("Верхняя граница меньше нижней!\n");
				if (x1 < -10 || x2 > 10) printf("Границы не входят в промежуток!\n");
			} while (x1 >= x2 || x1 < -10 || x2>10);

			do {
				printf("Введите единичный отрезок:\n");
				scanf_s("%lf", &ed);
				if (ed <= 0) printf("Единичный отрезок отрицательный!");
				if (ed > W / (2 * fabs(x1)) || ed > W / (2 * fabs(x2))) printf("Не весь введённый промежуток помещается на ось OX!");
			} while ( ed <= 0 || ed > W / (2*fabs(x1)) || ed > W / (2 * fabs(x2)) );
			
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			
			SDL_RenderDrawLine(renderer, 0, H/2,W, H/2);
			SDL_RenderDrawLine(renderer, W/2, 0, W/2, H);
			
			for (int i = W / 2; i <= W; i += ed)
				SDL_RenderDrawLine(renderer, i, H/2-1, i, H/2+1);
			for (int i = W / 2; i >= 0; i -= ed)
				SDL_RenderDrawLine(renderer, i, H / 2 - 1, i, H / 2 + 1);
			for (int i = H / 2; i < H;i += ed)
				SDL_RenderDrawLine(renderer, W/2-1, i, W/2+1, i);
			for (int i = H / 2; i >= 0;i -= ed)
				SDL_RenderDrawLine(renderer, W / 2 - 1, i, W / 2 + 1, i);

			int l=1;
			for (int j = W; j >= W - 3; j--)
			{
				SDL_RenderDrawLine(renderer, j, H/2-l, j, H/2+l);
				l++;
			}
			l = 1;
			for (int j = 0; j <=3; j++)
			{
				SDL_RenderDrawLine(renderer, W/2-l, j, W/2+l, j);
				l++;
			}
			
			/*for (int x = ed*x1+W/2; x <= ed*x2 + W/2;x++)
			SDL_RenderDrawPoint(renderer, x, H/2-ed*func(a,b,(x-W/2)/ed));*/				
			
			for (double i = x1; i<=x2; i+=0.1)
				SDL_RenderDrawPoint(renderer, ed*i+W/2, H / 2 - ed * func(a,b,i) );
			
			SDL_RenderPresent(renderer);
			SDL_Delay(10000);

			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}

void animation(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s("%s", SDL_GetError());
	}
	else
	{
		SDL_Window* window = NULL;
		window = SDL_CreateWindow(u8"Звёздное небо", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf_s("%s", SDL_GetError());
		}
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
			SNEG mas[1000];
			int sh = 1, ur = 736, rad=580, kolvo = 0;
			for (int i = 0;i < 1000;i++)
			{
				mas[i].x = rand() % 701-20;
				mas[i].y = rand() % 1450-1450;
			}
			for (int j = 0;j <= 1500;j++)								//кол-во изменений положения каждой снежинки
			{	
				if (j % 100 == 0) sh *=-1 ;							    //изменение направления смещения ветром
				
				SDL_SetRenderDrawColor(renderer, 0x0, 0x21, 0x37, 0x0);
				SDL_RenderClear(renderer);


				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
				for (int i = 0;i < 1000;i++)							//перебор снежинок
				{
					if (mas[i].y < 735) {							
						mas[i].y++;										
						mas[i].x += rand() % 3 - 1 + sh;				//смещение ветром + рандомом
					}
					else kolvo++;
					
					SDL_RenderDrawPoint(renderer, mas[i].x, mas[i].y);
				}
				
				if (kolvo % 100 == 0 && kolvo>0)
					ur--;												//увеличение уровня снега
				
				for (int h = 735;h >= ur;h--)							//заполнение слоями снега
				{
					SDL_RenderDrawLine(renderer, 600 - rad, h, rad, h);
					rad -= 20;
				}
				rad = 580;
				SDL_RenderPresent(renderer);
				SDL_Delay(15);
			}
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();

}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	setlocale(0, "");
	int n, lab;
	do {
		do {
			printf("Введите номер лабораторной(20 или 21) или 0, чтобы выйти:\n");
			scanf_s("%d", &lab);
			if (lab != 20 && lab != 21 && lab != 0) printf("Введите 20, 21 или 0!\n");
		} while (lab != 20 && lab != 21 && lab != 0);
		if (lab != 0)
		{
			if (lab == 20)
			{
				do {
					do {
						printf("Введите номер программы(1-3) или 4 - вернуться к списку лабораторных:\n");
						scanf_s("%d", &n);
						if (n != 1 && n != 2 && n != 3 && n != 4) printf("Введите число от 1 до 4!\n");
					} while (n != 1 && n != 2 && n != 3 && n != 4);
					if (n != 4)
					{
						switch (n)
						{
						case 1: first(); break;
						case 2: two(); break;
						case 3: three(); break;
						}
					}
				} while (n != 4);
			}
			else
			{
				animation();
			}
		}
	} while (lab != 0);
return 0;
}
