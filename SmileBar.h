#ifndef _SMILE_BAR_H
#define _SMILE_BAR_H

#include <SDL2/SDL.h>
#include <deque>
#include "Texture.h"
#include "Config.h"
#include "GameField.h"

class GameField;

class SmileBar
{
	friend class GameField;

	public:
		SmileBar(Config* config);
		~SmileBar() = default;
		void render(Texture& texture, SDL_Renderer* const renderer);
		void handleEvent(SDL_Event* event, GameField* gameField);

	private:
		Config* cfg;
		bool timerRunning;
		size_t startTimeSecs;
		size_t curTimeSecs;
		int minesInit;
		int minesLeft;
		size_t smileState;
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
