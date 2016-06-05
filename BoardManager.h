#ifndef _BOARD_MANAGER_H
#define _BOARD_MANAGER_H

#include "Board.h"

class BoardManager
{
	public:
		BoardManager() = default;
		~BoardManager() = default;
		Board* generateBoard(int rowCount, int colCount, int mineCount);

	private:
		int* generateMines(int rowCount, int colCount, int mineCount);
		CellValue toCellValue(int value);
};

#endif
