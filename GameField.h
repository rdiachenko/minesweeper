#ifndef _GAME_FIELD_H
#define _GAME_FIELD_H

#include <SDL2/SDL.h>
#include "Texture.h"

enum class CellState : const int;

class GameField
{
	public:
		GameField(size_t rows, size_t cols);
		~GameField();
		void setCellState(int r, int c, CellState state);
		void render(Texture& texture, SDL_Renderer* const renderer);
		void reset();

	private:
		size_t rs;
		size_t cs;
		CellState** field;
};

#endif
