#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <deque>
#include "GameField.h"
#include "Clip.h"
#include "Config.h"

static const size_t INF = 123456789;

enum class CellState
{
	INIT = Clip::CELL_INIT,
	PRESSED = Clip::CELL_PRESSED,
	FLAG = Clip::CELL_FLAG,
	FLAG_PRESSED = Clip::CELL_FLAG_PRESSED,
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

enum class GameState
{
	INIT,
	IN_PROGRESS,
	WIN,
	LOSE
};

GameField::GameField(size_t rows, size_t cols, size_t mines)
	: rs(rows), cs(cols), ms(mines), front(nullptr), back(nullptr), pressedRow(INF), pressedCol(INF), gameState(GameState::INIT)
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
		int y = 4 + Clip::clip(static_cast<const int>(SmileState::INIT))->h;
		for (size_t r = 0; r < rs; r++)
		{
			const SDL_Rect* clip = Clip::clip(static_cast<const int>(front[r][c]));
			texture.render(x, y, clip, renderer);
			y += clip->h;
		}
	}
}

void GameField::handleEvent(SDL_Event* event, SmileBar* smileBar)
{
	if (gameState != GameState::IN_PROGRESS && gameState != GameState::INIT)
	{
		return;
	}
	int x = (event->button).x;
	int y = (event->button).y;

	const SDL_Rect* clip = Clip::clip(static_cast<const int>(CellState::INIT));
	size_t r = (y - (4 + Clip::clip(static_cast<const int>(SmileState::INIT))->h)) / clip->h;
	size_t c = x / clip->w;
	auto btnType = (event->button).button;

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (insideField(x, y))
		{
			if (gameState == GameState::INIT)
			{
				gameState = GameState::IN_PROGRESS;
				smileBar->startTimer();
			}
			pressedRow = r;
			pressedCol = c;

			switch (front[r][c])
			{
				case CellState::INIT:
					front[r][c] = CellState::PRESSED;
					if (btnType == SDL_BUTTON_LEFT)
					{
						smileBar->smileState = SmileState::WONDER;
					}
					break;
				case CellState::FLAG:
					front[r][c] = CellState::FLAG_PRESSED;
					break;
				case CellState::QM_INIT:
					front[r][c] = CellState::QM_PRESSED;
					break;
				default:
					break;
			}
		}
	}
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		if (pressedRow < INF && pressedCol < INF)
		{
			switch (front[pressedRow][pressedCol])
			{
				case CellState::FLAG_PRESSED:
					if (btnType == SDL_BUTTON_LEFT)
					{
						front[pressedRow][pressedCol] = CellState::FLAG;
					}
					if (btnType == SDL_BUTTON_RIGHT)
					{
						front[pressedRow][pressedCol] = CellState::QM_INIT;
						smileBar->incrMines();
					}
					break;
				case CellState::QM_PRESSED:
					if (btnType == SDL_BUTTON_LEFT)
					{
						front[pressedRow][pressedCol] = CellState::QM_INIT;
					}
					else if (btnType == SDL_BUTTON_RIGHT)
					{
						front[pressedRow][pressedCol] = CellState::INIT;
					}
					break;
				case CellState::PRESSED:
					if (btnType == SDL_BUTTON_LEFT)
					{
						switch (back[pressedRow][pressedCol])
						{
							case CellState::PRESSED:
								smileBar->smileState = SmileState::INIT;
								openEmptyCells();
								break;
							case CellState::MINE_OK:
								smileBar->smileState = SmileState::LOSE;
								openAllCells();
								break;
							default:
								smileBar->smileState = SmileState::INIT;
								front[pressedRow][pressedCol] = back[pressedRow][pressedCol];
								break;
						}
					}
					else if (btnType == SDL_BUTTON_RIGHT)
					{
						front[pressedRow][pressedCol] = CellState::FLAG;
						smileBar->decrMines();
					}
					break;
				default:
					break;
			}
			pressedRow = INF;
			pressedCol = INF;
		}
	}
	checkWin();
	if (gameState == GameState::WIN)
	{
		smileBar->smileState = SmileState::WIN;
	}
	if (gameState == GameState::WIN || gameState == GameState::LOSE)
	{
		smileBar->stopTimer();
	}
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
	pressedRow = INF;
	pressedCol = INF;
	gameState = GameState::INIT;
}

bool GameField::insideField(int x, int y)
{
	return x >= 0 && x <= SCREEN_WIDTH && y >= 4 + Clip::clip(static_cast<const int>(SmileState::INIT))->h && y <= SCREEN_HEIGHT;
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
			case -1:
				back[r][c] = CellState::MINE_OK;
				break;
			case 0:
				back[r][c] = CellState::PRESSED;
				break;
			case 1:
				back[r][c] = CellState::MINES_1;
				break;
			case 2:
				back[r][c] = CellState::MINES_2;
				break;
			case 3:
				back[r][c] = CellState::MINES_3;
				break;
			case 4:
				back[r][c] = CellState::MINES_4;
				break;
			case 5:
				back[r][c] = CellState::MINES_5;
				break;
			case 6:
				back[r][c] = CellState::MINES_6;
				break;
			case 7:
				back[r][c] = CellState::MINES_7;
				break;
			case 8:
				back[r][c] = CellState::MINES_8;
				break;
			default:
				std::cout << "WARN: No mapping for cell value: " << cells[i]
					<< ". Empty cell will be used instead." << std::endl;
				back[r][c] = CellState::PRESSED;
		}
	}
}

void GameField::openEmptyCells()
{
	static const int m = 8;
	static int rShifts[m] = {-1, -1, 0, 1, 1, 1, 0, -1};
	static int cShifts[m] = {0, 1, 1, 1, 0, -1, -1, -1};
	bool seen[rs][cs];
	for (size_t r = 0; r < rs; r++)
	{
		std::fill_n(seen[r], cs, false);
	}
	std::deque<std::pair<int, int> > queue;
	queue.push_back({pressedRow, pressedCol});
	seen[pressedRow][pressedCol] = true;

	while (!queue.empty())
	{
		std::pair<int, int> cur = queue.front();
		queue.pop_front();
		front[cur.first][cur.second] = back[cur.first][cur.second];

		for (int k = 0; k < m; k++)
		{
			int nextr = rShifts[k] + cur.first;
			int nextc = cShifts[k] + cur.second;

			if (nextr >= 0 && static_cast<size_t>(nextr) < rs
					&& nextc >= 0 && static_cast<size_t>(nextc) < cs
					&& !seen[nextr][nextc]
					&& back[nextr][nextc] != CellState::MINE_OK
					&& back[cur.first][cur.second] == CellState::PRESSED
					&& front[nextr][nextc] == CellState::INIT)
			{
				seen[nextr][nextc] = true;
				queue.push_back({nextr, nextc});
			}
		}
	}
}

void GameField::openAllCells()
{
	gameState = GameState::LOSE;

	for (size_t r = 0; r < rs; r++)
	{
		for (size_t c = 0; c < cs; c++)
		{
			if (r == pressedRow && c == pressedCol)
			{
				front[pressedRow][pressedCol] = CellState::MINE_LOSE;
			}
			else if (front[r][c] == CellState::FLAG)
			{
				if (back[r][c] != CellState::MINE_OK)
				{
					front[r][c] = CellState::MINE_WRONG;
				}
			}
			else
			{
				front[r][c] = back[r][c];
			}
		}
	}
}

void GameField::checkWin()
{
	bool win = true;

	for (size_t r = 0; win && r < rs; r++)
	{
		for (size_t c = 0; win && c < cs; c++)
		{
			if ((front[r][c] != CellState::FLAG || back[r][c] != CellState::MINE_OK)
					&& front[r][c] != back[r][c])
			{
				win = false;
			}
		}
	}
	if (win)
	{
		gameState = GameState::WIN;
	}
}
