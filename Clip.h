#ifndef _CLIP_H
#define _CLIP_H

#include <SDL2/SDL.h>

class Clip
{
	public:
		static const int DIGIT_0 = 0;
		static const int DIGIT_1 = 1;
		static const int DIGIT_2 = 2;
		static const int DIGIT_3 = 3;
		static const int DIGIT_4 = 4;
		static const int DIGIT_5 = 5;
		static const int DIGIT_6 = 6;
		static const int DIGIT_7 = 7;
		static const int DIGIT_8 = 8;
		static const int DIGIT_9 = 9;

		static const int SMILE_INIT = 10;
		static const int SMILE_PRESSED = 11;
		static const int SMILE_O = 12;
		static const int SMILE_WIN = 13;
		static const int SMILE_LOSE = 14;

		static const int CELL_INIT = 15;
		static const int CELL_PRESSED = 16;
		static const int CELL_FLAG = 17;
		static const int CELL_FLAG_PRESSED = 18;
		static const int CELL_QM_INIT = 19;
		static const int CELL_QM_PRESSED = 20;
		static const int CELL_MINE_OK = 21;
		static const int CELL_MINE_LOSE = 22;
		static const int CELL_MINE_WRONG = 23;

		static const int CELL_1 = 24;
		static const int CELL_2 = 25;
		static const int CELL_3 = 26;
		static const int CELL_4 = 27;
		static const int CELL_5 = 28;
		static const int CELL_6 = 29;
		static const int CELL_7 = 30;
		static const int CELL_8 = 31;

		static const SDL_Rect* clip(const int type);
};

#endif
