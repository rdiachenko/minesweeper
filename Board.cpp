#include "Board.h"

Board::Board(int rowCount, int colCount)
	: rows(rowCount), cols(colCount), board(nullptr), openedCells(nullptr)
{
	board = new CellValue*[rows];
	openedCells = new bool*[rows];

	for (int i = 0; i < rows; ++i)
	{
		board[i] = new CellValue[cols];
		openedCells[i] = new bool[cols];

		for (int j = 0; j < cols; ++j)
		{
			board[i][j] = CellValue::EMPTY;
			openedCells[i][j] = false;
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < rows; ++i)
	{
		delete[] board[i];
		delete[] openedCells[i];
	}
	delete[] board;
	delete[] openedCells;
}

CellValue Board::getCellValue(int row, int col)
{
	return board[row][col];
}

void Board::setCellValue(int row, int col, CellValue val)
{
	board[row][col] = val;
}

bool Board::isCellOpened(int row, int col)
{
	return openedCells[row][col];
}

void Board::openCell(int row, int col)
{
	openedCells[row][col] = true;
}

