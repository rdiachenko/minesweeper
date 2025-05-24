#ifndef _SMILE_BAR_H
#define _SMILE_BAR_H

#include <SDL2/SDL.h>
#include <deque>
#include <memory>
#include "Texture.h"
#include "Config.h"
#include "GameField.h"

class GameField;

class SmileBar
{
	friend class GameField;

	public:
		explicit SmileBar(std::shared_ptr<Config> config);
		~SmileBar() = default;
		
		// Delete copy constructor and assignment operator
		SmileBar(const SmileBar&) = delete;
		SmileBar& operator=(const SmileBar&) = delete;
		
		void render(Texture& texture, SDL_Renderer* renderer);
		void handleEvent(const SDL_Event* event, GameField* gameField);

	private:
		std::shared_ptr<Config> cfg;
		bool timerRunning;
		size_t startTimeSecs;
		size_t curTimeSecs;
		int minesInit;
		int minesLeft;
		size_t smileState;
		
		size_t now() const;
		void startTimer();
		void stopTimer();
		void incrMines();
		void decrMines();
		void renderTimeCount(Texture& texture, SDL_Renderer* renderer);
		void renderMineCount(Texture& texture, SDL_Renderer* renderer);
		void renderSmile(Texture& texture, SDL_Renderer* renderer);
		void renderCount(int x, int y, int count, Texture& texture, SDL_Renderer* renderer);
		void reset();
		std::deque<int> toDigits(int val) const;
		bool insideSmile(int x, int y) const;
		
		// Validation helpers
		void validateRenderer(SDL_Renderer* renderer) const;
		void validateGameField(GameField* gameField) const;
};

#endif
