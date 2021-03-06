#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "main.h"
#include "Scene.h"

//functions
//starts SDL window, rendere and image processing
bool init();

//externs
int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
int BACKGROUND_WIDTH = 0;
int sceneWidth = 0;
int sceneHeight = 0;
SDL_Renderer* g_renderer = nullptr;
TTF_Font* g_font = nullptr;
TTF_Font* outline_font = nullptr;

//locals
SDL_Window* g_window = nullptr;
Scene scene;

//functions
bool init()
{
	bool success = true;
	//initialise SDL
	// SDL_Init() returns -1 if it fails
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
	}
	else
	{
		if (TTF_Init() == -1)
		{
			success = false;
		}
		else
		{
			g_font = TTF_OpenFont("Assets/Other/pixelmix_micro.ttf", 8);
			outline_font = TTF_OpenFont("Assets/Other/pixelmix_micro.ttf", 8);

			if (g_font == nullptr)
			{
				success = false;
			}
			if (outline_font == nullptr)
			{
				success = false;
			}
			else
			{
				TTF_SetFontOutline(outline_font, 1);
				//create the window
				g_window = SDL_CreateWindow("Wakinyan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
				if (g_window == nullptr)
				{
					success = false;
				}
				else
				{
					SDL_SetWindowFullscreen(g_window, SDL_TRUE);
					//create rendered
					g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
					if (g_renderer == nullptr)
					{
						success = false;
					}
					else
					{
						//initialise image loading
						int imgFlag = IMG_INIT_PNG;
						if (!(IMG_Init(imgFlag) & imgFlag))
						{
							success = false;
						}

						imgFlag = IMG_INIT_JPG;
						if (!(IMG_Init(imgFlag) & imgFlag))
						{
							success = false;
						}
					}
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//here is where the first scene needs to be created
	return scene.loadFromFile("Assets/Scenes/titleScreen.xml");
}

void close()
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	TTF_CloseFont(g_font);

	// no need to destroy scene, destructor is called when exiting anyway
	// was throwing an exception for accessing a memory address already emptied
//	scene.free();

	g_renderer = nullptr;
	g_renderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialise SDL");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to laod media");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			//application loop
			while (!quit)
			{
				//handle events in the queue
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
					}
					
					scene.update(e);
				}

				//clear screen
				SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderClear(g_renderer);

				scene.render();
				//draws what is in the renderer to the window
				SDL_RenderPresent(g_renderer);
			}
		}
	}
	close();

	return 0;
}
