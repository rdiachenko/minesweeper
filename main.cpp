#include <iostream>
#include "BoardManager.h"
#include "Board.h"
#include "GameLoop.h"

int main()
{
	BoardManager boardManager;
	int rows = 10;
	int cols = 20;
	int mines = 50;
	Board* board = boardManager.generateBoard(rows, cols, mines);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (board->getCellValue(i, j) == CellValue::MINE) std::cout << "* ";
			else std::cout << static_cast<int>(board->getCellValue(i, j)) << " ";
		}
		std::cout << "\n";
	}
	delete board;
	//GameLoop loop;
	//loop.run();
	return 0;
}
