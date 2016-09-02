#ifndef _SMILE_BAR_H
#define _SMILE_BAR_H

#include <SDL2/SDL.h>
#include <deque>
#include "Texture.h"

enum class SmileState : const int;

class SmileBar
{
	public:
		SmileBar(int mines);
		~SmileBar() = default;
		void incrTime();
		void incrMines();
		void decrMines();
		void setSmileState(SmileState state);
		void render(Texture& texture, SDL_Renderer* const renderer);

	private:
		int timeSecs;
		int minesLeft;
		SmileState smileState;
		void renderTimeCount(Texture& texture, SDL_Renderer* const renderer);
		void renderMineCount(Texture& texture, SDL_Renderer* const renderer);
		void renderSmile(Texture& texture, SDL_Renderer* const renderer);
		void renderCount(int x, int y, int count, Texture& texture, SDL_Renderer* const renderer);
		std::deque<int> toDigits(int val);
};

#endif
