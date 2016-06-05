#include <algorithm>
#include <random>
#include <chrono>
#include "BoardManager.h"

Board* BoardManager::generateBoard(int rowCount, int colCount, int mineCount)
{
	Board* board = new Board(rowCount, colCount);
	int* allCells = generateMines(rowCount, colCount, mineCount);
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			board->setCellValue(i, j, toCellValue(allCells[i * colCount + j]));
		}
	}
	delete[] allCells;
	return board;
}

int* BoardManager::generateMines(int rowCount, int colCount, int mineCount)
{
	int cellCount = rowCount * colCount;
	int* allCells = new int[cellCount];
	std::fill_n(allCells, cellCount, 0);
	std::fill_n(allCells, mineCount, static_cast<int>(CellValue::MINE));

	unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(allCells, allCells + cellCount, std::default_random_engine(seed));

	static const int neighbourCount = 8;
	static int rowNeighbours[neighbourCount] = {-1, -1, 0, 1, 1, 1, 0, -1};
	static int colNeighbours[neighbourCount] = {0, 1, 1, 1, 0, -1, -1, -1};

	for (int i = 0; i < cellCount; ++i)
	{
		if (allCells[i] == static_cast<int>(CellValue::MINE))
		{
			int row = i / colCount;
			int col = i % colCount;
			for (int k = 0; k < neighbourCount; ++k)
			{
				int neighbourRow = row + rowNeighbours[k];
				int neighbourCol = col + colNeighbours[k];
				if (neighbourRow >= 0 && neighbourRow < rowCount
						&& neighbourCol >= 0 && neighbourCol < colCount
						&& allCells[neighbourRow * colCount + neighbourCol] != static_cast<int>(CellValue::MINE))
				{
					++allCells[neighbourRow * colCount + neighbourCol];
				}
			}
		}
	}
	return allCells;
}

CellValue BoardManager::toCellValue(int value)
{
	switch (value)
	{
		case -1: return CellValue::MINE;
		case 0: return CellValue::EMPTY;
		case 1: return CellValue::MINE_CNT_1;
		case 2: return CellValue::MINE_CNT_2;
		case 3: return CellValue::MINE_CNT_3;
		case 4: return CellValue::MINE_CNT_4;
		case 5: return CellValue::MINE_CNT_5;
		case 6: return CellValue::MINE_CNT_6;
		case 7: return CellValue::MINE_CNT_7;
		case 8: return CellValue::MINE_CNT_8;
		default: return CellValue::UNDEFINED;
	}
}
