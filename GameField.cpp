#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "GameField.h"
#include "Clip.h"
#include "Config.h"

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

GameField::GameField(size_t rows, size_t cols, size_t mines) : rs(rows), cs(cols), ms(mines), front(nullptr), back(nullptr)
{
	front = new CellState*[rs];
	back = new CellState*[rs];
	for (size_t r = 0; r < rs; r++)
	{
		front[r] = new CellState[cs];
		back[r] = new CellState[cs];
		for (size_t c = 0; c < cs; c++)
		{
			front[r][c] = CellState::INIT;
			back[r][c] = CellState::PRESSED;
		}
	}
	generateField();
}

GameField::~GameField()
{
	for (size_t r = 0; r < rs; r++)
	{
		delete[] front[r];
		delete[] back[r];
	}
	delete[] front;
	delete[] back;
}

void GameField::render(Texture& texture, SDL_Renderer* const renderer)
{
	int x = 0;
	int xStep = Clip::clip(static_cast<const int>(CellState::INIT))->w;

	for (size_t c = 0; c < cs; c++, x += xStep)
	{
		int y = 30;
		for (size_t r = 0; r < rs; r++)
		{
			const SDL_Rect* clip = Clip::clip(static_cast<const int>(front[r][c]));
			texture.render(x, y, clip, renderer);
			y += clip->h;
		}
	}
}

void GameField::handleEvent(SDL_Event* event)
{
}

void GameField::reset()
{
	for (size_t r = 0; r < rs; r++)
	{
		for (size_t c = 0; c < cs; c++)
		{
			front[r][c] = CellState::INIT;
		}
	}
	generateField();
}

bool GameField::insideField(int x, int y)
{
	return x >= 0 && x <= SCREEN_WIDTH && y >= 30 && y <= SCREEN_HEIGHT;
}

void GameField::generateField()
{
	int n = rs * cs;
	int cells[n] = {0};
	std::fill_n(cells, ms, -1);

	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cells, cells + n, std::default_random_engine(seed));

	static const int m = 8;
	static int rShifts[m] = {-1, -1, 0, 1, 1, 1, 0, -1};
	static int cShifts[m] = {0, 1, 1, 1, 0, -1, -1, -1};

	for (int i = 0; i < n; i++)
	{   
		if (cells[i] < 0)
		{   
			int row = i / cs;
			int col = i % cs;
			for (int k = 0; k < m; k++)
			{   
				int rShift = row + rShifts[k];
				int cShift = col + cShifts[k];
				if (rShift >= 0 && static_cast<size_t>(rShift) < rs
						&& cShift >= 0 && static_cast<size_t>(cShift) < cs
						&& cells[rShift * cs + cShift] >= 0)
				{   
					cells[rShift * cs + cShift]++;
				}   
			}   
		}   
	}
	for (int i = 0; i < n; i++)
	{
		int r = i / cs;
		int c = i % cs;
		switch (cells[i])
		{
			case -1: back[r][c] = CellState::MINE_OK; break;
			case 0: back[r][c] = CellState::PRESSED; break;
			case 1: back[r][c] = CellState::MINES_1; break;
			case 2: back[r][c] = CellState::MINES_2; break;
			case 3: back[r][c] = CellState::MINES_3; break;
			case 4: back[r][c] = CellState::MINES_4; break;
			case 5: back[r][c] = CellState::MINES_5; break;
			case 6: back[r][c] = CellState::MINES_6; break;
			case 7: back[r][c] = CellState::MINES_7; break;
			case 8: back[r][c] = CellState::MINES_8; break;
			default:
					std::cout << "WARN: No mapping for cell value: " << cells[i]
					 << ". Empty cell will be used instead." << std::endl;
					back[r][c] = CellState::PRESSED;
		}
	}
}
