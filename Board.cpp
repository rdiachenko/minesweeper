#include "Board.h"

Board::Board(int rows, int cols, int mines) : rs(rows), cs(cols), ms(mines), board(nullptr)
{
	board = new int*[rs];
	for (int i = 0; i < rs; ++i)
	{
		board[i] = new int[cs];
	}
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
