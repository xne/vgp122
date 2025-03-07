#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

static bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL_Init() failed: " << SDL_GetError() << std::endl;
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		std::cout << "IMG_Init() failed: " << IMG_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(
		"Window Title",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL)
	{
		std::cout << "SDL_CreateWindow() failed: " << SDL_GetError() << std::endl;
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);

	if (screenSurface == NULL)
	{
		std::cout << "SDL_GetWindowSurface() failed: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

static SDL_Surface* loadImage(std::string path)
{
	SDL_Surface* image = IMG_Load(path.c_str());

	if (image == NULL)
	{
		std::cout << "IMG_Load() failed: " << IMG_GetError() << std::endl;
		return NULL;
	}
	
	return image;
}

static void quit()
{
	SDL_FreeSurface(screenSurface);
	screenSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

int main(int, char**)
{
	if (!init()) return EXIT_FAILURE;

	SDL_Surface* background = loadImage("images/bg.png");
	SDL_Surface* title = loadImage("images/logo.png");
	SDL_Surface* playButton = loadImage("images/play.png");

	SDL_Rect backgroundRect;
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = 800;
	backgroundRect.h = 600;

	SDL_BlitScaled(background, NULL, screenSurface, &backgroundRect);

	SDL_Rect titleRect;
	titleRect.x = 150;
	titleRect.y = 125;
	titleRect.w = 500;
	titleRect.h = 194;

	SDL_BlitScaled(title, NULL, screenSurface, &titleRect);

	SDL_Rect playButtonRect;
	playButtonRect.x = 300;
	playButtonRect.y = 350;
	playButtonRect.w = 200;
	playButtonRect.h = 66;

	SDL_BlitScaled(playButton, NULL, screenSurface, &playButtonRect);

	SDL_UpdateWindowSurface(window);

	SDL_Event event;
	bool running = true;
	
	while (running)
	{
		while (SDL_PollEvent(&event) == 1)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}

	SDL_FreeSurface(playButton);
	SDL_FreeSurface(title);
	SDL_FreeSurface(background);

	quit();

	return EXIT_SUCCESS;
}
