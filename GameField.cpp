#include "GameField.h"
#include "Clip.h"

enum class CellState
{
	INIT = Clip::CELL_INIT,
	PRESSED = Clip::CELL_PRESSED,
	FLAG = Clip::CELL_FLAG,
	QM_INIT = Clip::CELL_QM_INIT,
	QM_PRESSED = Clip::CELL_QM_PRESSED,
	MINE_OK = Clip::CELL_MINE_OK,
	MINE_LOSE = Clip::CELL_MINE_LOSE,
	MINE_WRONG = Clip::CELL_MINE_WRONG,
	MINES_1 = Clip::CELL_1,
	MINES_2 = Clip::CELL_2,
	MINES_3 = Clip::CELL_3,
	MINES_4 = Clip::CELL_4,
	MINES_5 = Clip::CELL_5,
	MINES_6 = Clip::CELL_6,
	MINES_7 = Clip::CELL_7,
	MINES_8 = Clip::CELL_8
};

GameField::GameField(size_t rows, size_t cols) : rs(rows), cs(cols)
{
	field = new CellState*[rs];
	for (size_t r = 0; r < rs; r++)
	{
		field[r] = new CellState[cs];
		for (size_t c = 0; c < cs; c++)
		{
			field[r][c] = CellState::INIT;
		}
	}
}

GameField::~GameField()
{
	for (size_t r = 0; r < rs; r++)
	{
		delete[] field[r];
	}
	delete[] field;
}

void GameField::setCellState(int r, int c, CellState state)
{
	field[r][c] = state;
}

void GameField::render(Texture& texture, SDL_Renderer* const renderer)
{
	int x = 0;
	int xStep = Clip::clip(Clip::CELL_INIT)->w;

	for (size_t c = 0; c < cs; c++, x += xStep)
	{
		int y = 30;
		for (size_t r = 0; r < rs; r++)
		{
			const SDL_Rect* clip = Clip::clip(static_cast<const int>(field[r][c]));
			texture.render(x, y, clip, renderer);
			y += clip->h;
		}
	}
}

void GameField::reset()
{
	for (size_t r = 0; r < rs; r++)
	{
		for (size_t c = 0; c < cs; c++)
		{
			field[r][c] = CellState::INIT;
		}
	}
}
