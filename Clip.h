#ifndef _CLIP_H
#define _CLIP_H

#include <SDL2/SDL.h>

class Clip
{
	public:
		static const int DIGIT_1 = 0;
		static const int DIGIT_2 = 1;
		static const int DIGIT_3 = 2;
		static const int DIGIT_4 = 3;
		static const int DIGIT_5 = 4;
		static const int DIGIT_6 = 5;
		static const int DIGIT_7 = 6;
		static const int DIGIT_8 = 7;
		static const int DIGIT_9 = 8;
		static const int DIGIT_0 = 9;

		static const int SMILE_INIT = 10;
		static const int SMILE_PRESSED = 11;
		static const int SMILE_O = 12;
		static const int SMILE_WIN = 13;
		static const int SMILE_LOSE = 14;

		static const int CELL_INIT = 15;
		static const int CELL_PRESSED = 16;
		static const int CELL_FLAG = 17;
		static const int CELL_QM_INIT = 18;
		static const int CELL_QM_PRESSED = 19;
		static const int CELL_BOMB_OK = 20;
		static const int CELL_BOMB_LOSE = 21;
		static const int CELL_BOMB_WRONG = 22;

		static const int CELL_1 = 23;
		static const int CELL_2 = 24;
		static const int CELL_3 = 25;
		static const int CELL_4 = 26;
		static const int CELL_5 = 27;
		static const int CELL_6 = 28;
		static const int CELL_7 = 29;
		static const int CELL_8 = 30;

		static const SDL_Rect* clip(const int type);
};

#endif
