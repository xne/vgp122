#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return 1;
	}

	surface = SDL_GetWindowSurface(window);

	if (!surface)
	{
		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));

	SDL_UpdateWindowSurface(window);

	system("pause");

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
