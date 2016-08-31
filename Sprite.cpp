#include "Sprite.h"

static const int CLIPS_COUNT = 31;
static const SDL_Rect clips[CLIPS_COUNT] =
{
	{0, 0, 13, 23},
	{14, 0, 13, 23},
	{28, 0, 13, 23},
	{42, 0, 13, 23},
	{56, 0, 13, 23},
	{70, 0, 13, 23},
	{84, 0, 13, 23},
	{98, 0, 13, 23},
	{112, 0, 13, 23},
	{126, 0, 13, 23},
	{0, 24, 26, 26},
	{27, 24, 26, 26},
	{54, 24, 26, 26},
	{81, 24, 26, 26},
	{108, 24, 26, 26},
	{0, 51, 16, 16},
	{17, 51, 16, 16},
	{34, 51, 16, 16},
	{51, 51, 16, 16},
	{68, 51, 16, 16},
	{85, 51, 16, 16},
	{102, 51, 16, 16},
	{119, 51, 16, 16},
	{0, 68, 16, 16},
	{17, 68, 16, 16},
	{34, 68, 16, 16},
	{51, 68, 16, 16},
	{68, 68, 16, 16},
	{85, 68, 16, 16},
	{102, 68, 16, 16},
	{119, 68, 16, 16}
};

const int Sprite::TIME_1 = 0;
const int Sprite::TIME_2 = 1;
const int Sprite::TIME_3 = 2;
const int Sprite::TIME_4 = 3;
const int Sprite::TIME_5 = 4;
const int Sprite::TIME_6 = 5;
const int Sprite::TIME_7 = 6;
const int Sprite::TIME_8 = 7;
const int Sprite::TIME_9 = 8;
const int Sprite::TIME_0 = 9;

const int Sprite::SMILE_INIT = 10;
const int Sprite::SMILE_PRESSED = 11;
const int Sprite::SMILE_O = 12;
const int Sprite::SMILE_WIN = 13;
const int Sprite::SMILE_LOSE = 14;

const int Sprite::CELL_INIT = 15;
const int Sprite::CELL_PRESSED = 16;
const int Sprite::CELL_FLAG = 17;
const int Sprite::CELL_QM_INIT = 18;
const int Sprite::CELL_QM_PRESSED = 19;
const int Sprite::CELL_BOMB_OK = 20;
const int Sprite::CELL_BOMB_LOSE = 21;
const int Sprite::CELL_BOMB_WRONG = 22;

const int Sprite::CELL_1 = 23;
const int Sprite::CELL_2 = 24;
const int Sprite::CELL_3 = 25;
const int Sprite::CELL_4 = 26;
const int Sprite::CELL_5 = 27;
const int Sprite::CELL_6 = 28;
const int Sprite::CELL_7 = 29;
const int Sprite::CELL_8 = 30;

const SDL_Rect* Sprite::clip(const int type)
{
	return &clips[type];
}
