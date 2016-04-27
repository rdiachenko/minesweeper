#ifndef _GAME_LOOP_H
#define _GAME_LOOP_H

#include <SDL2/SDL.h>

class GameLoop
{
	public:
		GameLoop() : window(nullptr), renderer(nullptr), running(true) {}
		~GameLoop()
		{
			cleanup();
		}
		void run();

	private:
		bool running;
		SDL_Window* window;
		SDL_Renderer* renderer;
		bool init();
		void onEvent(SDL_Event* event);
		void cleanup();
};

#endif
