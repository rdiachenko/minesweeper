#ifndef _SMILE_BAR_H
#define _SMILE_BAR_H

#include <SDL2/SDL.h>
#include <deque>
#include "Texture.h"
#include "Clip.h"

enum class SmileState : const int;

class SmileBar
{
	public:
		SmileBar(int mines);
		~SmileBar() = default;
		void incrTime();
		void incrMines();
		void decrMines();
		void render(Texture& texture, SDL_Renderer* const renderer);
		void handleEvent(SDL_Event* event);

	private:
		int timeSecs;
		int minesInit;
		int minesLeft;
		SmileState smileState;
		void renderTimeCount(Texture& texture, SDL_Renderer* const renderer);
		void renderMineCount(Texture& texture, SDL_Renderer* const renderer);
		void renderSmile(Texture& texture, SDL_Renderer* const renderer);
		void renderCount(int x, int y, int count, Texture& texture, SDL_Renderer* const renderer);
		void reset();
		std::deque<int> toDigits(int val);
		bool insideSmile(int x, int y);
};

#endif
