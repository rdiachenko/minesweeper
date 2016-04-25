#ifndef _BOARD_H
#define _BOARD_H

#include <vector>

class Board
{
	static const int MINE = 9;

	public:
		Board(int rows, int cols, int mines);
		~Board();
		int get(int r, int c);

	private:
		void setupMines();
		std::vector<std::pair<int, int> > generateMines();
		int rs;
		int cs;
		int ms;
		int** board;
};

#endif 
