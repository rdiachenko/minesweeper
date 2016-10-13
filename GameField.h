#ifndef _GAME_FIELD_H
#define _GAME_FIELD_H

#include <SDL2/SDL.h>
#include "Texture.h"

enum class CellState : const int;

class GameField
{
	public:
		GameField(size_t rows, size_t cols, size_t mines);
		~GameField();
		void render(Texture& texture, SDL_Renderer* const renderer);
		void handleEvent(SDL_Event* event);

	private:
		size_t rs;
		size_t cs;
		size_t ms;
		CellState** front;
		CellState** back;
		size_t pressedRow;
		size_t pressedCol;
		void reset();
		bool insideField(int x, int y);
		void generateField();
		void openEmptyCells();
		void openAllCells();
		bool gameOver();
};

#endif
