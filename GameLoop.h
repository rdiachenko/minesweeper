#ifndef _GAME_LOOP_H
#define _GAME_LOOP_H

#include <SDL2/SDL.h>

class GameLoop
{
	public:
		GameLoop();
		~GameLoop();
		void run();

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		bool running;
		void onEvent(SDL_Event* event);
};

#endif
