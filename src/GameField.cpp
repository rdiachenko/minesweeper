#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <deque>
#include "GameField.h"

static const size_t INF = 123456789;

enum class GameState
{
	INIT,
	IN_PROGRESS,
	WIN,
	LOSE
};

GameField::GameField(Config* config)
	: cfg(config), rs(cfg->getFieldRowCnt()), cs(cfg->getFieldColCnt()), ms(cfg->getMineCnt()), front(nullptr), back(nullptr), pressedRow(INF), pressedCol(INF), gameState(GameState::INIT)
{
	front = new size_t*[rs];
	back = new size_t*[rs];
	for (size_t r = 0; r < rs; r++)
	{
		front[r] = new size_t[cs];
		back[r] = new size_t[cs];
		for (size_t c = 0; c < cs; c++)
		{
			front[r][c] = Clip::CELL_INIT;
			back[r][c] = Clip::CELL_PRESSED;
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
	int xStep = cfg->getClip(Clip::CELL_INIT)->w;

	for (size_t c = 0; c < cs; c++, x += xStep)
	{
		int y = 2 + cfg->getClip(Clip::SMILE_INIT)->h + 2; // top bar height
		for (size_t r = 0; r < rs; r++)
		{
			const SDL_Rect* clip = cfg->getClip(front[r][c]);
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
	size_t r = (y - (2 + cfg->getClip(Clip::SMILE_INIT)->h + 2)) / clip->h;
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
	for (size_t r = 0; r < rs; r++)
	{
		for (size_t c = 0; c < cs; c++)
		{
			front[r][c] = Clip::CELL_INIT;
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
		&& y >= 2 + cfg->getClip(Clip::SMILE_INIT)->h + 2 && y <= static_cast<int>(cfg->getWinHeight());
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
				back[r][c] = Clip::CELL_MINE;
				break;
			case 0:
				back[r][c] = Clip::CELL_PRESSED;
				break;
			case 1:
				back[r][c] = Clip::CELL_1;
				break;
			case 2:
				back[r][c] = Clip::CELL_2;
				break;
			case 3:
				back[r][c] = Clip::CELL_3;
				break;
			case 4:
				back[r][c] = Clip::CELL_4;
				break;
			case 5:
				back[r][c] = Clip::CELL_5;
				break;
			case 6:
				back[r][c] = Clip::CELL_6;
				break;
			case 7:
				back[r][c] = Clip::CELL_7;
				break;
			case 8:
				back[r][c] = Clip::CELL_8;
				break;
			default:
				std::cout << "WARN: No mapping for cell value: " << cells[i]
					<< ". Empty cell will be used instead." << std::endl;
				back[r][c] = Clip::CELL_PRESSED;
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
					&& back[nextr][nextc] != Clip::CELL_MINE
					&& back[cur.first][cur.second] == Clip::CELL_PRESSED
					&& front[nextr][nextc] == Clip::CELL_INIT)
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
				front[pressedRow][pressedCol] = Clip::CELL_MINE_LOSE;
			}
			else if (front[r][c] == Clip::CELL_FLAG)
			{
				if (back[r][c] != Clip::CELL_MINE)
				{
					front[r][c] = Clip::CELL_MINE_WRONG;
				}
			}
			else
			{
				front[r][c] = back[r][c];
			}
		}
	}
}

void GameField::openAllFlags()
{
	for (size_t r = 0; r < rs; r++)
	{
		for (size_t c = 0; c < cs; c++)
		{
			if (back[r][c] == Clip::CELL_MINE)
			{
				front[r][c] = Clip::CELL_FLAG;
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

	for (size_t r = 0; win && r < rs; r++)
	{
		for (size_t c = 0; win && c < cs; c++)
		{
			win &= back[r][c] == Clip::CELL_MINE || front[r][c] == back[r][c];
		}
	}
	return win;
}
