#include <iostream>
#include "GameLoop.h"
#include "Config.h"

using std::cerr;

void GameLoop::run()
{
	if (!init()) cerr << "Failed to initialize game loop\n";
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			onEvent(&event);
		}
		SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, BACKGROUND_COLOR_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
}

bool GameLoop::init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL could not be initialized: " << SDL_GetError() << '\n';
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == nullptr)
		{
			cerr << "Window could not be created: " << SDL_GetError() << '\n';
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == nullptr)
			{
				cerr << "Renderer could not be created: " << SDL_GetError() << '\n';
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, BACKGROUND_COLOR_OPAQUE);
				SDL_RenderPresent(renderer);
			}
		}
	}
	return success;
}

void GameLoop::onEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
	{
		running = false;
	}
}

void GameLoop::cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
	SDL_Quit();
}
