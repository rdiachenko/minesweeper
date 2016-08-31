#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL2/SDL.h>

class Sprite
{
	public:
		static const int TIME_1;
		static const int TIME_2;
		static const int TIME_3;
		static const int TIME_4;
		static const int TIME_5;
		static const int TIME_6;
		static const int TIME_7;
		static const int TIME_8;
		static const int TIME_9;
		static const int TIME_0;

		static const int SMILE_INIT;
		static const int SMILE_PRESSED;
		static const int SMILE_O;
		static const int SMILE_WIN;
		static const int SMILE_LOSE;

		static const int CELL_INIT;
		static const int CELL_PRESSED;
		static const int CELL_FLAG;
		static const int CELL_QM_INIT;
		static const int CELL_QM_PRESSED;
		static const int CELL_BOMB_OK;
		static const int CELL_BOMB_LOSE;
		static const int CELL_BOMB_WRONG;

		static const int CELL_1;
		static const int CELL_2;
		static const int CELL_3;
		static const int CELL_4;
		static const int CELL_5;
		static const int CELL_6;
		static const int CELL_7;
		static const int CELL_8;

		static const SDL_Rect* clip(const int type);
};

#endif
