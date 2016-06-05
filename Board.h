#ifndef _BOARD_H
#define _BOARD_H

#include <vector>

enum class CellValue
{
	MINE = -1,
	EMPTY = 0,
	MINE_CNT_1 = 1,
	MINE_CNT_2 = 2,
	MINE_CNT_3 = 3,
	MINE_CNT_4 = 4,
	MINE_CNT_5 = 5,
	MINE_CNT_6 = 6,
	MINE_CNT_7 = 7,
	MINE_CNT_8 = 8,
	UNDEFINED = -777
};

class Board
{
	public:
		Board(int rowCount, int colCount);
		~Board();

		CellValue getCellValue(int row, int col);
		void setCellValue(int row, int col, CellValue val);
		bool isCellOpened(int row, int col);
		void openCell(int row, int col);

	private:
		int rows;
		int cols;
		CellValue** board;
		bool** openedCells;
};

#endif 
