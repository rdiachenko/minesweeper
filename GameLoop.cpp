#include <iostream>
#include "GameLoop.h"
#include "Config.h"

GameLoop::GameLoop() : window(nullptr), renderer(nullptr), running(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not be initialized: " << SDL_GetError() << '\n';
	}
	else
	{
		window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == nullptr)
		{
			std::cerr << "Window could not be created: " << SDL_GetError() << '\n';
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == nullptr)
			{
				std::cerr << "Renderer could not be created: " << SDL_GetError() << '\n';
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, BACKGROUND_COLOR_OPAQUE);
				SDL_RenderPresent(renderer);
			}
		}
	}
}

GameLoop::~GameLoop()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	running = false;
	SDL_Quit();
}

void GameLoop::run()
{
	running = true;
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

void GameLoop::onEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
	{
		running = false;
	}
}
