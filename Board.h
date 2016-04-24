#ifndef _BOARD_H
#define _BOARD_H

class Board
{
	public:
		Board(int rows, int cols, int mines);
		~Board();
		int get(int r, int c);

	private:
		int rs;
		int cs;
		int ms;
		int** board;
};

#endif 
