#include <algorithm>
#include <random>
#include <chrono>
#include "Board.h"

Board::Board(int rows, int cols, int mines) : rs(rows), cs(cols), ms(mines), board(nullptr)
{
	board = new int*[rs];
	for (int i = 0; i < rs; ++i)
	{
		board[i] = new int[cs];

		for (int j = 0; j < cs; ++j)
		{
			board[i][j] = 0;
		}
	}
	setupMines();
}

Board::~Board()
{
	for (int i = 0; i < rs; ++i)
	{
		delete[] board[i];
	}
	delete[] board;
}

int Board::get(int r, int c)
{
	return board[r][c];
}

void Board::setupMines()
{
	for (const auto& mine : generateMines())
	{
		int i = mine.first;
		int j = mine.second;
		board[i][j] = MINE;
		static const int m = 8;
		static int is[m] = {-1, -1, 0, 1, 1, 1, 0, -1};
		static int js[m] = {0, 1, 1, 1, 0, -1, -1, -1};
		for (int k = 0; k < m; ++k)
		{
			int ni = i + is[k];
			int nj = j + js[k];
			if (ni >= 0 && ni < rs && nj >= 0 && nj < cs && board[ni][nj] != MINE)
			{
				++board[ni][nj];
			}
		}
	}
}

std::vector<std::pair<int, int> > Board::generateMines()
{
	int n = rs * cs;
	bool allCells[n] = {false};
	for (int i = 0; i < ms; ++i)
	{
		allCells[i] = true;
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(allCells, allCells + n, std::default_random_engine(seed));
	std::vector<std::pair<int, int> > mines;
	for (int i = 0; i < n; ++i)
	{
		if (allCells[i])
		{
			mines.push_back({i / cs, i % cs});
		}
	}
	return std::move(mines);
}
