#include <iostream>
#include "GameLoop.h"
#include "Config.h"
#include "Texture.h"

GameLoop::GameLoop() : window(nullptr), renderer(nullptr), smileBar(nullptr), gameField(nullptr), running(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Can't initialize SDL: " << SDL_GetError() << '\n';
	}
	else
	{
		window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == nullptr)
		{
			std::cerr << "Can't create window: " << SDL_GetError() << '\n';
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == nullptr)
			{
				std::cerr << "Can't create renderer: " << SDL_GetError() << '\n';
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, BACKGROUND_COLOR_OPAQUE);
				SDL_RenderPresent(renderer);
				smileBar = new SmileBar(99);
				gameField = new GameField(16, 30, 99);
			}
		}
	}
}

GameLoop::~GameLoop()
{
	if (smileBar != nullptr)
	{
		delete smileBar;
	}
	if (gameField != nullptr)
	{
		delete gameField;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	running = false;
	SDL_Quit();
}

void GameLoop::run()
{
	running = true;
	SDL_Event event;
	Texture texture(renderer, SPRITE_PATH);

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			onEvent(&event);
		}
		SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B, BACKGROUND_COLOR_OPAQUE);
		SDL_RenderClear(renderer);
		smileBar->render(texture, renderer);
		gameField->render(texture, renderer);
		SDL_RenderPresent(renderer);
	}
}

void GameLoop::onEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
	{
		running = false;
	}
	else
	{
		gameField->handleEvent(event, smileBar);
		smileBar->handleEvent(event, gameField);
	}
}
