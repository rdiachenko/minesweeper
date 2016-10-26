#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <deque>
#include "GameField.h"

static const size_t INF = 123456789;

static const int shiftCount = 8;
static int rowShifts[shiftCount] = {-1, -1, 0, 1, 1, 1, 0, -1};
static int colShifts[shiftCount] = {0, 1, 1, 1, 0, -1, -1, -1};

enum class GameState
{
	INIT,
	IN_PROGRESS,
	WIN,
	LOSE
};

GameField::GameField(Config* config)
	: cfg(config), rowCount(cfg->getFieldRowCnt()), colCount(cfg->getFieldColCnt()), mineCount(cfg->getMineCnt()), front(nullptr), back(nullptr), pressedRow(INF), pressedCol(INF), gameState(GameState::INIT), topBarHeight(0)
{
	front = new size_t*[rowCount];
	back = new size_t*[rowCount];
	for (size_t row = 0; row < rowCount; row++)
	{
		front[row] = new size_t[colCount];
		back[row] = new size_t[colCount];

		for (size_t col = 0; col < colCount; col++)
		{
			front[row][col] = Clip::CELL_INIT;
			back[row][col] = Clip::CELL_PRESSED;
		}
	}
	topBarHeight = 2 + cfg->getClip(Clip::SMILE_INIT)->h + 2;
	generateField();
}

GameField::~GameField()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		delete[] front[row];
		delete[] back[row];
	}
	delete[] front;
	delete[] back;
}

void GameField::render(Texture& texture, SDL_Renderer* const renderer)
{
	int x = 0;
	int xStep = cfg->getClip(Clip::CELL_INIT)->w;

	for (size_t col = 0; col < colCount; col++, x += xStep)
	{
		int y = topBarHeight;
		for (size_t row = 0; row < rowCount; row++)
		{
			const SDL_Rect* clip = cfg->getClip(front[row][col]);
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

	const SDL_Rect* clip = cfg->getClip(Clip::CELL_INIT);
	size_t row = (y - topBarHeight) / clip->h;
	size_t col = x / clip->w;
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
			pressedRow = row;
			pressedCol = col;

			switch (front[pressedRow][pressedCol])
			{
				case Clip::CELL_INIT:
					front[pressedRow][pressedCol] = Clip::CELL_PRESSED;
					if (btnType == SDL_BUTTON_LEFT)
					{
						smileBar->smileState = Clip::SMILE_WONDER;
					}
					break;
				case Clip::CELL_FLAG:
					front[pressedRow][pressedCol] = Clip::CELL_FLAG_PRESSED;
					break;
				case Clip::CELL_QM:
					front[pressedRow][pressedCol] = Clip::CELL_QM_PRESSED;
					break;
				default:
					pressedRow = INF;
					pressedCol = INF;
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
				case Clip::CELL_FLAG_PRESSED:
					if (btnType == SDL_BUTTON_LEFT)
					{
						front[pressedRow][pressedCol] = Clip::CELL_FLAG;
					}
					if (btnType == SDL_BUTTON_RIGHT)
					{
						front[pressedRow][pressedCol] = Clip::CELL_QM;
						smileBar->incrMines();
					}
					break;
				case Clip::CELL_QM_PRESSED:
					if (btnType == SDL_BUTTON_LEFT)
					{
						front[pressedRow][pressedCol] = Clip::CELL_QM;
					}
					else if (btnType == SDL_BUTTON_RIGHT)
					{
						front[pressedRow][pressedCol] = Clip::CELL_INIT;
					}
					break;
				case Clip::CELL_PRESSED:
					if (btnType == SDL_BUTTON_LEFT)
					{
						switch (back[pressedRow][pressedCol])
						{
							case Clip::CELL_PRESSED:
								smileBar->smileState = Clip::SMILE_INIT;
								openEmptyCells();
								break;
							case Clip::CELL_MINE:
								smileBar->smileState = Clip::SMILE_LOSE;
								openAllCells();
								break;
							default:
								smileBar->smileState = Clip::SMILE_INIT;
								front[pressedRow][pressedCol] = back[pressedRow][pressedCol];
								break;
						}
					}
					else if (btnType == SDL_BUTTON_RIGHT)
					{
						front[pressedRow][pressedCol] = Clip::CELL_FLAG;
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
	if (isWin())
	{
		gameState = GameState::WIN;
		smileBar->smileState = Clip::SMILE_WIN;
		openAllFlags();
	}
	if (gameState == GameState::WIN || gameState == GameState::LOSE)
	{
		smileBar->stopTimer();
	}
}

void GameField::reset()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t col = 0; col < colCount; col++)
		{
			front[row][col] = Clip::CELL_INIT;
		}
	}
	generateField();
	pressedRow = INF;
	pressedCol = INF;
	gameState = GameState::INIT;
}

bool GameField::insideField(int x, int y)
{
	return x >= 0 && x <= static_cast<int>(cfg->getWinWidth())
		&& y >= topBarHeight && y <= static_cast<int>(cfg->getWinHeight());
}

void GameField::generateField()
{
	const int totalCellCount = rowCount * colCount;
	int* cells = new int[totalCellCount];
	std::fill_n(cells, totalCellCount, 0);
	std::fill_n(cells, mineCount, -1);

	size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cells, cells + totalCellCount, std::default_random_engine(seed));

	for (int i = 0; i < totalCellCount; i++)
	{   
		if (cells[i] < 0)
		{   
			int row = i / colCount;
			int col = i % colCount;
			for (int k = 0; k < shiftCount; k++)
			{   
				int rowShift = row + rowShifts[k];
				int colShift = col + colShifts[k];
				if (rowShift >= 0 && static_cast<size_t>(rowShift) < rowCount
						&& colShift >= 0 && static_cast<size_t>(colShift) < colCount
						&& cells[rowShift * colCount + colShift] >= 0)
				{   
					cells[rowShift * colCount + colShift]++;
				}   
			}   
		}   
	}
	for (int i = 0; i < totalCellCount; i++)
	{
		int row = i / colCount;
		int col = i % colCount;
		switch (cells[i])
		{
			case -1:
				back[row][col] = Clip::CELL_MINE;
				break;
			case 0:
				back[row][col] = Clip::CELL_PRESSED;
				break;
			case 1:
				back[row][col] = Clip::CELL_1;
				break;
			case 2:
				back[row][col] = Clip::CELL_2;
				break;
			case 3:
				back[row][col] = Clip::CELL_3;
				break;
			case 4:
				back[row][col] = Clip::CELL_4;
				break;
			case 5:
				back[row][col] = Clip::CELL_5;
				break;
			case 6:
				back[row][col] = Clip::CELL_6;
				break;
			case 7:
				back[row][col] = Clip::CELL_7;
				break;
			case 8:
				back[row][col] = Clip::CELL_8;
				break;
			default:
				std::cout << "WARN: No mapping for cell value: " << cells[i]
					<< ". Empty cell will be used instead." << std::endl;
				back[row][col] = Clip::CELL_PRESSED;
		}
	}
	delete[] cells;
}

void GameField::openEmptyCells()
{
	bool** seen = new bool*[rowCount];
	for (size_t row = 0; row < rowCount; row++)
	{
		seen[row] = new bool[colCount];
		std::fill_n(seen[row], colCount, false);
	}
	std::deque<std::pair<int, int> > queue;
	queue.push_back({pressedRow, pressedCol});
	seen[pressedRow][pressedCol] = true;

	while (!queue.empty())
	{
		std::pair<int, int> cell = queue.front();
		int row = cell.first;
		int col = cell.second;
		queue.pop_front();
		front[row][col] = back[row][col];

		for (int k = 0; k < shiftCount; k++)
		{
			int nextRow = rowShifts[k] + row;
			int nextCol = colShifts[k] + col;

			if (nextRow >= 0 && static_cast<size_t>(nextRow) < rowCount
					&& nextCol >= 0 && static_cast<size_t>(nextCol) < colCount
					&& !seen[nextRow][nextCol]
					&& back[nextRow][nextCol] != Clip::CELL_MINE
					&& back[row][col] == Clip::CELL_PRESSED
					&& front[nextRow][nextCol] == Clip::CELL_INIT)
			{
				seen[nextRow][nextCol] = true;
				queue.push_back({nextRow, nextCol});
			}
		}
	}
	for (size_t row = 0; row < rowCount; row++)
	{
		delete[] seen[row];
	}
	delete[] seen;
}

void GameField::openAllCells()
{
	gameState = GameState::LOSE;

	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t col = 0; col < colCount; col++)
		{
			if (row == pressedRow && col == pressedCol)
			{
				front[pressedRow][pressedCol] = Clip::CELL_MINE_LOSE;
			}
			else if (front[row][col] == Clip::CELL_FLAG)
			{
				if (back[row][col] != Clip::CELL_MINE)
				{
					front[row][col] = Clip::CELL_MINE_WRONG;
				}
			}
			else
			{
				front[row][col] = back[row][col];
			}
		}
	}
}

void GameField::openAllFlags()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t col = 0; col < colCount; col++)
		{
			if (back[row][col] == Clip::CELL_MINE)
			{
				front[row][col] = Clip::CELL_FLAG;
			}
		}
	}
}

bool GameField::isWin()
{
	if (gameState == GameState::LOSE)
	{
		return false;
	}
	bool win = true;

	for (size_t row = 0; win && row < rowCount; row++)
	{
		for (size_t col = 0; win && col < colCount; col++)
		{
			win &= back[row][col] == Clip::CELL_MINE || front[row][col] == back[row][col];
		}
	}
	return win;
}
