#ifndef _GAME_FIELD_H
#define _GAME_FIELD_H

#include <SDL2/SDL.h>
#include "Config.h"
#include "Texture.h"
#include "SmileBar.h"

enum class GameState;

class SmileBar;

class GameField
{
	friend class SmileBar;

	public:
		GameField(Config* config);
		~GameField();
		void render(Texture& texture, SDL_Renderer* const renderer);
		void handleEvent(SDL_Event* event, SmileBar* smileBar);

	private:
		Config* cfg;
		size_t rs;
		size_t cs;
		size_t ms;
		size_t** front;
		size_t** back;
		size_t pressedRow;
		size_t pressedCol;
		GameState gameState;
		void reset();
		bool insideField(int x, int y);
		void generateField();
		void openEmptyCells();
		void openAllCells();
		void checkWin();
};

#endif
