#include <iostream>
#include "Board.h"
#include "GameLoop.h"

int main()
{
	Board board(10, 10, 50);
	GameLoop loop;
	loop.run();
	return 0;
}
