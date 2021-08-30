#pragma comment(lib, "SDL2_mixer.lib")
#include "SDL_mixer.h"
#include "SDL.h"
#include "stdlib.h"
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <math.h>
#define W 800
#define H 600
#define BALL_COUNT 5

void loadmusic(Mix_Music*& fon)
{
	fon = Mix_LoadMUS("fon.wav");
	Mix_PlayMusic(fon, -1);
}

void sound(Mix_Chunk*& Sound)
{
	Sound = Mix_LoadWAV("puff.wav");
	Mix_PlayChannel(-1, Sound, 0);
}

SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font) //Создание текстуры текста
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 255,0,0 };
	SDL_Color back_color = { 0,0,0 };
	textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

void draw_text(SDL_Renderer*& renderer, SDL_Texture* texture) //Отображение текста
{
	SDL_Rect rect = { 0,0, 70, 200 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void draw_text_point(SDL_Renderer*& renderer, SDL_Texture* texture, SDL_Rect ball) //Отображение очков на шаре
{
	SDL_Rect rect = { ball.x + int(ball.w / 4), ball.y + int(ball.h / 4), int(ball.w / 2), int(ball.h / 2) };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void init_balls1(SDL_Rect balls[], int count) //Задание высоты, ширины и координат
{
	for (int i = 0; i < count; i++)
	{
		balls[i] = { 100 + 120 * i, rand() % (H - 150) + 30,50 + 5 * i ,50 + 5 * i };
	}
}
void init_balls2(SDL_Rect balls[], int count) //Задание высоты, ширины и координат
{
	int t;
	for (int i = 0; i < count; i++)
	{
		t = rand() % 361;
		balls[i] = { W / 2 + int(60 * i * cos(3.14 * t / 180)),H / 2 + int(60 * i * sin(3.14 * t / 180)),60 ,60 };
	}
}
void draw_balls(SDL_Renderer*& renderer, SDL_Rect balls[], int count, SDL_Texture* texture) //Рисование шаров
{
	for (int i = 0; i < count; i++)
	{
		if (balls[i].w == 0) continue;
		SDL_RenderCopy(renderer, texture, NULL, &balls[i]);
	}
}
bool is_ball_hit(SDL_Rect ball, int x, int y)		//Попадание в шар
{
	if (ball.w == 0) return false;
	int centerX = ball.x + ball.w / 2;
	int centerY = ball.y + ball.h / 2;
	int radius = ball.w / 2;
	return sqrt((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y)) < radius;
}


void one()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) printf("%s", SDL_GetError());
	else
	{
		SDL_Window* window = SDL_CreateWindow("Click the balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
		if (window == NULL) printf("%s", SDL_GetError());
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

			Mix_Init(0);
			Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
			Mix_Music* fon = NULL;
			Mix_Chunk* Sound = NULL;
			

			SDL_Rect balls[BALL_COUNT];
			init_balls1(balls, BALL_COUNT);

			SDL_Surface* ballImage = IMG_Load("1.bmp");
			SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
			SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer, ballImage);
			SDL_FreeSurface(ballImage);


			TTF_Init();
			TTF_Font* my_font = TTF_OpenFont("font.ttf", 100);
			SDL_Texture* textTexture;

			int k = 0;
			char text[10]; //Окно подсчёта очков
			_itoa_s(k, text, 10);
			textTexture = get_text_texture(renderer, text, my_font);


			int arr[BALL_COUNT];
			char text_point[10];
			SDL_Texture* textPointTexture[BALL_COUNT];
			for (int i = 0;i < BALL_COUNT;i++)
			{ //Создание текстур очков на шарах
				arr[i] = rand() % 10 + 1;
				_itoa_s(arr[i], text_point, 10);
				textPointTexture[i] = get_text_texture(renderer, text_point, my_font);
			}

			int s=0;

			SDL_Event event;
			bool quit = false;
			while (!quit)
			{
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT)
						quit = true;
					if (event.type == SDL_MOUSEBUTTONDOWN &&
						event.button.button == SDL_BUTTON_LEFT)
					{
						for (int i = 0; i < BALL_COUNT; i++)
						{
							if (is_ball_hit(balls[i], event.button.x, event.button.y))
							{
								s++;
								balls[i].w = balls[i].h = 0;
								k += arr[i];
								_itoa_s(k, text, 10);
								SDL_DestroyTexture(textTexture);
								textTexture = get_text_texture(renderer, text, my_font);
								sound(Sound);
							}
						}
					}
				}

				SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);

				SDL_RenderClear(renderer);

				draw_balls(renderer, balls, BALL_COUNT, ballTexture);
				for (int i = 0;i < BALL_COUNT;i++)
					draw_text_point(renderer, textPointTexture[i], balls[i]);
				draw_text(renderer, textTexture);

				SDL_RenderPresent(renderer);
				if (s == BALL_COUNT) break;
			}
			Mix_FreeMusic(fon);
			Mix_FreeChunk(Sound);
			Mix_CloseAudio();
			SDL_DestroyTexture(textTexture);
			SDL_DestroyTexture(ballTexture);
			TTF_CloseFont(my_font);
			TTF_Quit();
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
	}
}


void two()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) printf("%s", SDL_GetError());
	else
	{
		SDL_Window* window = SDL_CreateWindow("Click the balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
		if (window == NULL) printf("%s", SDL_GetError());
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

			Mix_Init(0);
			Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
			Mix_Chunk* Sound = NULL;
			Mix_Music* fon = NULL;

			SDL_Rect balls[BALL_COUNT];
			init_balls1(balls, BALL_COUNT);

			SDL_Surface* ballImage = IMG_Load("1.bmp");
			SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
			SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer, ballImage);
			SDL_FreeSurface(ballImage);


			TTF_Init();
			TTF_Font* my_font = TTF_OpenFont("font.ttf", 100);
			SDL_Texture* textTexture;

			int k = 0;
			char text[10];										//Окно подсчёта очков
			_itoa_s(k, text, 10);
			textTexture = get_text_texture(renderer, text, my_font);


			int arr[BALL_COUNT];
			char text_point[10];
			SDL_Texture* textPointTexture[BALL_COUNT];
			for (int i = 0;i < BALL_COUNT;i++)
			{												//Создание текстур очков на шарах
				arr[i] = rand() % 10 + 1;
				_itoa_s(arr[i], text_point, 10);
				textPointTexture[i] = get_text_texture(renderer, text_point, my_font);
			}

			int t[BALL_COUNT];
			for (int i = 0;i < BALL_COUNT;i++)		//Начальные углы поворота шаров
				t[i] = rand() % 361;

			int s=0;	//переменная для проверки удалены ли все шары

			loadmusic(fon);

			SDL_Event event;
			bool quit = false;
			while (!quit)
			{
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT)
						quit = true;
					if (event.type == SDL_MOUSEBUTTONDOWN &&
						event.button.button == SDL_BUTTON_LEFT)
					{
						for (int i = 0; i < BALL_COUNT; i++)
						{
							if (is_ball_hit(balls[i], event.button.x, event.button.y))
							{
								s++;
								balls[i].w = balls[i].h = 0;
								k += arr[i];
								_itoa_s(k, text, 10);
								SDL_DestroyTexture(textTexture);
								textTexture = get_text_texture(renderer, text, my_font);
								sound(Sound);
							}
						}
					}
				}

				SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
				SDL_RenderClear(renderer);

				for (int i = 0;i < BALL_COUNT;i++)
				{
					if (balls[i].w!=0)
					{
						t[i] = (t[i] + 1) % 360;
						balls[i].w = 20 + int(0.5 * (t[i] % 70));
						balls[i].h = 20 + int(0.5 * (t[i] % 70));
						balls[i].x = W / 2 + int(60 * i * cos(3.14 * t[i] / 180)) - balls[i].w;
						balls[i].y = H / 2 + int(60 * i * sin(3.14 * t[i] / 180)) - balls[i].h;
					}
				}

				draw_balls(renderer, balls, BALL_COUNT, ballTexture);
				for (int i = 0;i < BALL_COUNT;i++)
					draw_text_point(renderer, textPointTexture[i], balls[i]);
				draw_text(renderer, textTexture);

				SDL_RenderPresent(renderer);
				SDL_Delay(15);
				if (s == BALL_COUNT) break;
			}
			Mix_FreeChunk(Sound);
			Mix_FreeMusic(fon);
			Mix_CloseAudio();
			SDL_DestroyTexture(textTexture);
			SDL_DestroyTexture(ballTexture);
			TTF_CloseFont(my_font);
			TTF_Quit();
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
	}
}

//Функции для задания 3
SDL_Texture* get_text_texture1(SDL_Renderer*& renderer, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 255,0,0 };
	SDL_Color back_color = { 0,0,0 };
	textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

SDL_Texture* get_text_texture2(SDL_Renderer*& renderer, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 0,255,0 };
	SDL_Color back_color = { 0,0,0 };
	textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

void draw_text1(SDL_Renderer*& renderer, SDL_Texture* texture) 
{
	SDL_Rect rect = { 20,H-20 ,40, 20 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void draw_text2(SDL_Renderer*& renderer, SDL_Texture* texture) 
{
	SDL_Rect rect = { 80,H - 20 ,40, 20 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void draw_mines(SDL_Renderer*& renderer, SDL_Rect mines[], SDL_Texture* texture) 
{
	for (int i = 0; i < 3; i++)
	{
		if (mines[i].w == 0) continue;
		SDL_RenderCopy(renderer, texture, NULL, &mines[i]);
	}
}
void draw_traps(SDL_Renderer*& renderer, SDL_Rect traps[], SDL_Texture* texture)
{
	for (int i = 0; i < 3; i++)
	{
		if (traps[i].w == 0) continue;
		SDL_RenderCopy(renderer, texture, NULL, &traps[i]);
	}
}
bool is_hit_(SDL_Rect mines, SDL_Rect rect_pers)	
{
	if (mines.w == 0) return false;
	int centerPersx = rect_pers.x + rect_pers.w / 2;
	int centerPersy = rect_pers.y + rect_pers.h / 2;
	int x= mines.x + mines.w / 2;
	int y = mines.y + mines.h / 2;
	return sqrt((centerPersx - x) * (centerPersx - x) + (centerPersy - y) * (centerPersy - y)) < 35;
}

void wall1(SDL_Rect *wall)
{
	wall[0] = {0,0,W-20,20};
	wall[1] = {W-20,0,20,H-20};
	wall[2] = {20,H-20,W-20,20};
	wall[3] = {0,20,20,H-20};
	wall[4] = {240,20,40,280};
	wall[5] = {500,80,40,500};
	wall[6] = {640,20,40,500};
}
void wall2(SDL_Rect* wall)
{
	wall[0] = { 0,0,W - 20,20 };
	wall[1] = { W - 20,0,20,H - 20 };
	wall[2] = { 20,H - 20,W - 20,20 };
	wall[3] = { 0,20,20,H - 20 };
	wall[4] = { 100,100,60,340 };
	wall[5] = { 160,100,500,40 };
	wall[6] = { 660,100,40,400 };
}
void wall3(SDL_Rect* wall)
{
	wall[0] = { 0,0,W - 20,20 };
	wall[1] = { W - 20,0,20,H - 20 };
	wall[2] = { 20,H - 20,W - 20,20 };
	wall[3] = { 0,20,20,H - 20 };
	wall[4] = { 20,400,620,80 };
	wall[5] = { 120,200,660,100 };
	wall[6] = { 380,20,80,120 };
}

void level1(SDL_Window* window, SDL_Renderer* renderer,TTF_Font* my_font,int &win, int &quitGame)
{
	
	int life = 2;
	int mines = 0;

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;
	
	SDL_Texture* textTexture1;
	SDL_Texture* textTexture2;
	char text[10];									
	_itoa_s(life, text, 10);
	textTexture1 = get_text_texture1(renderer, text, my_font);
	_itoa_s(mines, text, 10);
	textTexture2 = get_text_texture2(renderer, text, my_font);

	SDL_Rect GAME = { 0,0,W,H };
	SDL_Texture* textTextureGAMEOVER;
	char gameover[10] = "GAME OVER";
	textTextureGAMEOVER= get_text_texture1(renderer, gameover, my_font);
	SDL_Texture* textTextureWIN;
	char gamewin[20] = "Level 1 passsed";
	textTextureWIN = get_text_texture2(renderer, gamewin, my_font);

	SDL_Surface* locationImage = IMG_Load("grass.bmp");
	SDL_SetColorKey(locationImage, SDL_TRUE, SDL_MapRGB(locationImage->format, 255, 255, 255));
	SDL_Texture* locationTexture = SDL_CreateTextureFromSurface(renderer, locationImage);
	SDL_FreeSurface(locationImage);
	SDL_Rect location = { 0,0,W,H };

	SDL_Surface* wallImage = IMG_Load("wall.bmp");
	SDL_SetColorKey(wallImage, SDL_TRUE, SDL_MapRGB(wallImage->format, 255, 255, 255));
	SDL_Texture* wallTexture = SDL_CreateTextureFromSurface(renderer, wallImage);
	SDL_FreeSurface(wallImage);
	SDL_Rect Walls[7];
	wall1(Walls);

	SDL_Surface* persImage = IMG_Load("pers.bmp");
	SDL_SetColorKey(persImage, SDL_TRUE, SDL_MapRGB(persImage->format, 255, 255, 255));
	SDL_Texture* persTexture = SDL_CreateTextureFromSurface(renderer, persImage);
	SDL_FreeSurface(persImage);
	SDL_Rect rect_pers = { 120,60,48,48 };	

	SDL_Surface* mineImage = IMG_Load("mine.bmp");
	SDL_SetColorKey(mineImage, SDL_TRUE, SDL_MapRGB(mineImage->format, 255, 255, 255));
	SDL_Texture* mineTexture = SDL_CreateTextureFromSurface(renderer,mineImage);
	SDL_FreeSurface(mineImage);
	SDL_Rect Mines[3];
	Mines[0] = { 40,550,30,30 };
	Mines[1] = { 500,30,30,30 };
	Mines[2] = { 730,40,30,30 };

	SDL_Surface* trapImage = IMG_Load("trap.bmp");
	SDL_SetColorKey(trapImage, SDL_TRUE, SDL_MapRGB(trapImage->format, 255, 255, 255));
	SDL_Texture* trapTexture = SDL_CreateTextureFromSurface(renderer, trapImage);
	SDL_FreeSurface(trapImage);
	SDL_Rect Traps[3];
	Traps[0] = {120,300,30,30};
	Traps[1] = {375,250,30,30};
	Traps[2] = {600,350,30,30};
	
	SDL_Event event;
	bool quit = false;

	win = 0;
	
	int a=0;

	loadmusic(fon);
	
	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				quitGame = 1;
				win = 1;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_w))
			{
				for (int i = 0;i < 7;i++)
					if (abs(Walls[i].y + Walls[i].h-rect_pers.y)<1 
						&& rect_pers.x <= Walls[i].x + Walls[i].w && rect_pers.x + rect_pers.w >= Walls[i].x) a = 1;
					if (a != 1) rect_pers.y-=4;
					a = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_s))
			{
				for (int i = 0;i < 7;i++)
					if (abs(rect_pers.y + rect_pers.h - Walls[i].y) < 1 
						&& rect_pers.x <= Walls[i].x + Walls[i].w && rect_pers.x + rect_pers.w >= Walls[i].x) a = 1;
					if (a != 1) rect_pers.y+=4;
					a = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_d))
			{
				for (int i = 0;i < 7;i++)
					if (abs(Walls[i].x-(rect_pers.x+rect_pers.w))<1 
						&& rect_pers.y <= Walls[i].y + Walls[i].h && rect_pers.y + rect_pers.h >= Walls[i].y) a = 1;
					if (a != 1) rect_pers.x+=4;
					a = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_a))
			{
				for (int i = 0;i < 7;i++)
					if (abs(rect_pers.x-(Walls[i].x + Walls[i].w))<1 
						&& rect_pers.y <= Walls[i].y + Walls[i].h && rect_pers.y + rect_pers.h >= Walls[i].y) a = 1;
					if (a != 1) rect_pers.x-=4;
					a = 0;
			}
			for (int i = 0;i < 3;i++)
			{
				if (is_hit_(Mines[i], rect_pers))
				{
					Mines[i].h = Mines[i].w = 0;
					mines++;
					_itoa_s(mines,text,10);
					SDL_DestroyTexture(textTexture2);
					textTexture2 = get_text_texture2(renderer,text,my_font);
					sound(Sound);
				}
				if (is_hit_(Traps[i], rect_pers))
				{
					Traps[i].h = Traps[i].w = 0;
					life--;
					_itoa_s(life, text, 10);
					SDL_DestroyTexture(textTexture1);
					textTexture1 = get_text_texture1(renderer, text, my_font);
					sound(Sound);
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		
		SDL_RenderCopy(renderer, locationTexture, NULL, &location);
		for (int i = 0;i < 7;i++)
			SDL_RenderCopy(renderer, wallTexture, NULL, &Walls[i]);
		draw_text1(renderer,textTexture1);
		draw_text2(renderer, textTexture2);
		draw_mines(renderer,Mines,mineTexture);
		draw_traps(renderer,Traps,trapTexture);
		SDL_RenderCopy(renderer, persTexture, NULL, &rect_pers);
		
		if (mines == 3) win = 1;
		if (mines == 3)
		{
			SDL_RenderCopy(renderer, textTextureWIN, NULL, &GAME);
			SDL_RenderPresent(renderer);
			SDL_Delay(3000);
		}

		if (life==0)
		{
			SDL_RenderCopy(renderer, textTextureGAMEOVER, NULL, &GAME);
			SDL_RenderPresent(renderer);
			SDL_Delay(3000);
		}
		SDL_RenderPresent(renderer);
		if (life == 0) break;
		if (win == 1) break;
	}
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
	Mix_CloseAudio();
	SDL_DestroyTexture(textTextureGAMEOVER);
	SDL_DestroyTexture(textTextureWIN);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(trapTexture);
	SDL_DestroyTexture(mineTexture);
	SDL_DestroyTexture(locationTexture);
	SDL_DestroyTexture(wallTexture);
	SDL_DestroyTexture(persTexture);
}



void level2(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* my_font, int& win, int &quitGame)
{

	int life = 2;
	int mines = 0;

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;
	
	SDL_Texture* textTexture1;
	SDL_Texture* textTexture2;
	char text[10];
	_itoa_s(life, text, 10);
	textTexture1 = get_text_texture1(renderer, text, my_font);
	_itoa_s(mines, text, 10);
	textTexture2 = get_text_texture2(renderer, text, my_font);

	SDL_Rect GAME = { 0,0,W,H };
	SDL_Texture* textTextureGAMEOVER;
	char gameover[10] = "GAME OVER";
	textTextureGAMEOVER = get_text_texture1(renderer, gameover, my_font);
	SDL_Texture* textTextureWIN;
	char gamewin[20] = "Level 2 passsed";
	textTextureWIN = get_text_texture2(renderer, gamewin, my_font);

	SDL_Surface* locationImage = IMG_Load("grass.bmp");
	SDL_SetColorKey(locationImage, SDL_TRUE, SDL_MapRGB(locationImage->format, 255, 255, 255));
	SDL_Texture* locationTexture = SDL_CreateTextureFromSurface(renderer, locationImage);
	SDL_FreeSurface(locationImage);
	SDL_Rect location = { 0,0,W,H };

	SDL_Surface* wallImage = IMG_Load("wall.bmp");
	SDL_SetColorKey(wallImage, SDL_TRUE, SDL_MapRGB(wallImage->format, 255, 255, 255));
	SDL_Texture* wallTexture = SDL_CreateTextureFromSurface(renderer, wallImage);
	SDL_FreeSurface(wallImage);
	SDL_Rect Walls[7];
	wall2(Walls);

	SDL_Surface* persImage = IMG_Load("pers.bmp");
	SDL_SetColorKey(persImage, SDL_TRUE, SDL_MapRGB(persImage->format, 255, 255, 255));
	SDL_Texture* persTexture = SDL_CreateTextureFromSurface(renderer, persImage);
	SDL_FreeSurface(persImage);
	SDL_Rect rect_pers = { 40,240,48,48 };

	SDL_Surface* mineImage = IMG_Load("mine.bmp");
	SDL_SetColorKey(mineImage, SDL_TRUE, SDL_MapRGB(mineImage->format, 255, 255, 255));
	SDL_Texture* mineTexture = SDL_CreateTextureFromSurface(renderer, mineImage);
	SDL_FreeSurface(mineImage);
	SDL_Rect Mines[3];
	Mines[0] = { 180,160,30,30 };
	Mines[1] = { 700,30,30,30 };
	Mines[2] = { 380,520,30,30 };

	SDL_Surface* trapImage = IMG_Load("trap.bmp");
	SDL_SetColorKey(trapImage, SDL_TRUE, SDL_MapRGB(trapImage->format, 255, 255, 255));
	SDL_Texture* trapTexture = SDL_CreateTextureFromSurface(renderer, trapImage);
	SDL_FreeSurface(trapImage);
	SDL_Rect Traps[3];
	Traps[0] = { 40,350,30,30 };
	Traps[1] = { 580,540,30,30 };
	Traps[2] = { 220,220,30,30 };

	SDL_Event event;
	bool quit = false;

	win = 0;

	int a = 0;

	loadmusic(fon);

	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				quitGame = 1;
				win = 1;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_w))
			{
				for (int i = 0;i < 7;i++)
					if (abs(Walls[i].y + Walls[i].h - rect_pers.y) < 1
						&& rect_pers.x <= Walls[i].x + Walls[i].w && rect_pers.x + rect_pers.w >= Walls[i].x) a = 1;
				if (a != 1) rect_pers.y -= 4;
				a = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_s))
			{
				for (int i = 0;i < 7;i++)
					if (abs(rect_pers.y + rect_pers.h - Walls[i].y) < 1
						&& rect_pers.x <= Walls[i].x + Walls[i].w && rect_pers.x + rect_pers.w >= Walls[i].x) a = 1;
				if (a != 1) rect_pers.y += 4;
				a = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_d))
			{
				for (int i = 0;i < 7;i++)
					if (abs(Walls[i].x - (rect_pers.x + rect_pers.w)) < 1
						&& rect_pers.y <= Walls[i].y + Walls[i].h && rect_pers.y + rect_pers.h >= Walls[i].y) a = 1;
				if (a != 1) rect_pers.x += 4;
				a = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_a))
			{
				for (int i = 0;i < 7;i++)
					if (abs(rect_pers.x - (Walls[i].x + Walls[i].w)) < 1
						&& rect_pers.y <= Walls[i].y + Walls[i].h && rect_pers.y + rect_pers.h >= Walls[i].y) a = 1;
				if (a != 1) rect_pers.x -= 4;
				a = 0;
			}
			for (int i = 0;i < 3;i++)
			{
				if (is_hit_(Mines[i], rect_pers))
				{
					Mines[i].h = Mines[i].w = 0;
					mines++;
					_itoa_s(mines, text, 10);
					SDL_DestroyTexture(textTexture2);
					textTexture2 = get_text_texture2(renderer, text, my_font);
					sound(Sound);
				}
				if (is_hit_(Traps[i], rect_pers))
				{
					Traps[i].h = Traps[i].w = 0;
					life--;
					_itoa_s(life, text, 10);
					SDL_DestroyTexture(textTexture1);
					textTexture1 = get_text_texture1(renderer, text, my_font);
					sound(Sound);
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, locationTexture, NULL, &location);
		for (int i = 0;i < 7;i++)
			SDL_RenderCopy(renderer, wallTexture, NULL, &Walls[i]);
		draw_text1(renderer, textTexture1);
		draw_text2(renderer, textTexture2);
		draw_mines(renderer, Mines, mineTexture);
		draw_traps(renderer, Traps, trapTexture);
		SDL_RenderCopy(renderer, persTexture, NULL, &rect_pers);

		if (mines == 3) win = 1;
		if (mines == 3)
		{
			SDL_RenderCopy(renderer, textTextureWIN, NULL, &GAME);
			SDL_RenderPresent(renderer);
			SDL_Delay(3000);
		}

		if (life == 0)
		{
			SDL_RenderCopy(renderer, textTextureGAMEOVER, NULL, &GAME);
			SDL_RenderPresent(renderer);
			SDL_Delay(3000);
		}
		SDL_RenderPresent(renderer);
		if (life == 0) break;
		if (win == 1) break;
	}
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
	Mix_CloseAudio();
	SDL_DestroyTexture(textTextureGAMEOVER);
	SDL_DestroyTexture(textTextureWIN);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(trapTexture);
	SDL_DestroyTexture(mineTexture);
	SDL_DestroyTexture(locationTexture);
	SDL_DestroyTexture(wallTexture);
	SDL_DestroyTexture(persTexture);
}




void level3(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* my_font, int& win, int &quitGame)
{

	int life = 2;
	int mines = 0;

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;

	SDL_Texture* textTexture1;
	SDL_Texture* textTexture2;
	char text[10];
	_itoa_s(life, text, 10);
	textTexture1 = get_text_texture1(renderer, text, my_font);
	_itoa_s(mines, text, 10);
	textTexture2 = get_text_texture2(renderer, text, my_font);

	SDL_Rect GAME = { 0,0,W,H };
	SDL_Texture* textTextureGAMEOVER;
	char gameover[10] = "GAME OVER";
	textTextureGAMEOVER = get_text_texture1(renderer, gameover, my_font);
	SDL_Texture* textTextureWIN;
	char gamewin[20] = "Level 3 passsed";
	textTextureWIN = get_text_texture2(renderer, gamewin, my_font);

	SDL_Surface* locationImage = IMG_Load("grass.bmp");
	SDL_SetColorKey(locationImage, SDL_TRUE, SDL_MapRGB(locationImage->format, 255, 255, 255));
	SDL_Texture* locationTexture = SDL_CreateTextureFromSurface(renderer, locationImage);
	SDL_FreeSurface(locationImage);
	SDL_Rect location = { 0,0,W,H };

	SDL_Surface* wallImage = IMG_Load("wall.bmp");
	SDL_SetColorKey(wallImage, SDL_TRUE, SDL_MapRGB(wallImage->format, 255, 255, 255));
	SDL_Texture* wallTexture = SDL_CreateTextureFromSurface(renderer, wallImage);
	SDL_FreeSurface(wallImage);
	SDL_Rect Walls[7];
	wall3(Walls);

	SDL_Surface* persImage = IMG_Load("pers.bmp");
	SDL_SetColorKey(persImage, SDL_TRUE, SDL_MapRGB(persImage->format, 255, 255, 255));
	SDL_Texture* persTexture = SDL_CreateTextureFromSurface(renderer, persImage);
	SDL_FreeSurface(persImage);
	SDL_Rect rect_pers = { 40,520,48,48 };

	SDL_Surface* mineImage = IMG_Load("mine.bmp");
	SDL_SetColorKey(mineImage, SDL_TRUE, SDL_MapRGB(mineImage->format, 255, 255, 255));
	SDL_Texture* mineTexture = SDL_CreateTextureFromSurface(renderer, mineImage);
	SDL_FreeSurface(mineImage);
	SDL_Rect Mines[3];
	Mines[0] = { 720,40,30,30 };
	Mines[1] = { 340,30,30,30 };
	Mines[2] = { 350,350,30,30 };

	SDL_Surface* trapImage = IMG_Load("trap.bmp");
	SDL_SetColorKey(trapImage, SDL_TRUE, SDL_MapRGB(trapImage->format, 255, 255, 255));
	SDL_Texture* trapTexture = SDL_CreateTextureFromSurface(renderer, trapImage);
	SDL_FreeSurface(trapImage);
	SDL_Rect Traps[3];
	Traps[0] = { 40,200,30,30 };
	Traps[1] = { 680,400,30,30 };
	Traps[2] = { 520,150,30,30 };

	SDL_Event event;
	bool quit = false;

	win = 0;

	int a = 0;

	loadmusic(fon);

	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				quitGame = 1;
				win = 1;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_w))
			{
				for (int i = 0;i < 7;i++)
					if (abs(Walls[i].y + Walls[i].h - rect_pers.y) < 1
						&& rect_pers.x <= Walls[i].x + Walls[i].w && rect_pers.x + rect_pers.w >= Walls[i].x) a = 1;
				if (a != 1) rect_pers.y -= 4;
				a = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_s))
			{
				for (int i = 0;i < 7;i++)
					if (abs(rect_pers.y + rect_pers.h - Walls[i].y) < 1
						&& rect_pers.x <= Walls[i].x + Walls[i].w && rect_pers.x + rect_pers.w >= Walls[i].x) a = 1;
				if (a != 1) rect_pers.y += 4;
				a = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_d))
			{
				for (int i = 0;i < 7;i++)
					if (abs(Walls[i].x - (rect_pers.x + rect_pers.w)) < 1
						&& rect_pers.y <= Walls[i].y + Walls[i].h && rect_pers.y + rect_pers.h >= Walls[i].y) a = 1;
				if (a != 1) rect_pers.x += 4;
				a = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_a))
			{
				for (int i = 0;i < 7;i++)
					if (abs(rect_pers.x - (Walls[i].x + Walls[i].w)) < 1
						&& rect_pers.y <= Walls[i].y + Walls[i].h && rect_pers.y + rect_pers.h >= Walls[i].y) a = 1;
				if (a != 1) rect_pers.x -= 4;
				a = 0;
			}
			for (int i = 0;i < 3;i++)
			{
				if (is_hit_(Mines[i], rect_pers))
				{
					Mines[i].h = Mines[i].w = 0;
					mines++;
					_itoa_s(mines, text, 10);
					SDL_DestroyTexture(textTexture2);
					textTexture2 = get_text_texture2(renderer, text, my_font);
					sound(Sound);
				}
				if (is_hit_(Traps[i], rect_pers))
				{
					Traps[i].h = Traps[i].w = 0;
					life--;
					_itoa_s(life, text, 10);
					SDL_DestroyTexture(textTexture1);
					textTexture1 = get_text_texture1(renderer, text, my_font);
					sound(Sound);
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, locationTexture, NULL, &location);
		for (int i = 0;i < 7;i++)
			SDL_RenderCopy(renderer, wallTexture, NULL, &Walls[i]);
		draw_text1(renderer, textTexture1);
		draw_text2(renderer, textTexture2);
		draw_mines(renderer, Mines, mineTexture);
		draw_traps(renderer, Traps, trapTexture);
		SDL_RenderCopy(renderer, persTexture, NULL, &rect_pers);

		if (mines == 3) win = 1;
		if (mines == 3)
		{
			SDL_RenderCopy(renderer, textTextureWIN, NULL, &GAME);
			SDL_RenderPresent(renderer);
			SDL_Delay(3000);
		}

		if (life == 0)
		{
			SDL_RenderCopy(renderer, textTextureGAMEOVER, NULL, &GAME);
			SDL_RenderPresent(renderer);
			SDL_Delay(3000);
		}
		SDL_RenderPresent(renderer);
		if (life == 0) break;
		if (win == 1) break;
	}
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
	Mix_CloseAudio();
	SDL_DestroyTexture(textTextureGAMEOVER);
	SDL_DestroyTexture(textTextureWIN);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(trapTexture);
	SDL_DestroyTexture(mineTexture);
	SDL_DestroyTexture(locationTexture);
	SDL_DestroyTexture(wallTexture);
	SDL_DestroyTexture(persTexture);
}

void three()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) printf("%s", SDL_GetError());
	else
	{
		SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
		if (window == NULL) printf("%s", SDL_GetError());
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

			
			
			TTF_Init();
			TTF_Font* my_font = TTF_OpenFont("font.ttf", 100);
			
			int win;
			int quitGame=0;
			do {
				level1(window, renderer, my_font, win, quitGame);
			} while (win==0);
			if (win == 1 && quitGame != 1)
			{
				win = 0;
				do {
					level2(window, renderer, my_font, win,quitGame);
				} while (win == 0);
			}
			if (win == 1 && quitGame !=1)
			{
				win = 0;
				do {
					level3(window, renderer, my_font, win, quitGame);
				} while (win == 0);
			}
			
			TTF_CloseFont(my_font);
			TTF_Quit();
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
	}
}
int main(int argc, char** argv)
{
	setlocale(0, "");
	srand(time(NULL));
	int n;
	do {
		do {
			printf("Введите номер задания (1-3) или 0 для выхода:\n");
			scanf_s("%d", &n);
		} while (n != 0 && n != 1 && n != 2 && n != 3);
		switch (n)
		{
		case 1: one(); break;
		case 2: two(); break;
		case 3: three(); break;
		}
	} while (n != 0);
	return 0;
}
