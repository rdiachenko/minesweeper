#ifndef _GAME_FIELD_H
#define _GAME_FIELD_H

#include <SDL2/SDL.h>
#include "Texture.h"
//#include "FieldModel.h"

enum class CellState : const int;

class GameField
{
	public:
		GameField(size_t rows, size_t cols);
		~GameField();
		void render(Texture& texture, SDL_Renderer* const renderer);
		void handleEvent(SDL_Event* event);

	private:
		size_t rs;
		size_t cs;
		CellState** field;
		void reset();
		bool insideField(int x, int y);
		//FieldModel* model;
};

#endif
