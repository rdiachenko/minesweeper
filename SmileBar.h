#ifndef _SMILE_BAR_H
#define _SMILE_BAR_H

#include <SDL2/SDL.h>
#include <deque>
#include "Texture.h"
#include "Clip.h"
#include "GameField.h"

enum class SmileState : const int
{
	INIT = Clip::SMILE_INIT,
	PRESSED = Clip::SMILE_PRESSED,
	WONDER = Clip::SMILE_O,
	WIN = Clip::SMILE_WIN,
	LOSE = Clip::SMILE_LOSE
};

class GameField;

class SmileBar
{
	friend class GameField;

	public:
		SmileBar(int mines);
		~SmileBar() = default;
		void render(Texture& texture, SDL_Renderer* const renderer);
		void handleEvent(SDL_Event* event, GameField* gameField);

	private:
		bool timerRunning;
		size_t startTimeSecs;
		size_t curTimeSecs;
		int minesInit;
		int minesLeft;
		SmileState smileState;
		size_t now();
		void startTimer();
		void stopTimer();
		void incrMines();
		void decrMines();
		void renderTimeCount(Texture& texture, SDL_Renderer* const renderer);
		void renderMineCount(Texture& texture, SDL_Renderer* const renderer);
		void renderSmile(Texture& texture, SDL_Renderer* const renderer);
		void renderCount(int x, int y, int count, Texture& texture, SDL_Renderer* const renderer);
		void reset();
		std::deque<int> toDigits(int val);
		bool insideSmile(int x, int y);
};

#endif
