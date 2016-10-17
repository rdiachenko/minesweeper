#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <map>
#include <SDL2/SDL.h>

class Config
{
	public:
		static const size_t BACKGROUND_COLOR_R = 0xD5;
		static const size_t BACKGROUND_COLOR_G = 0xD5;
		static const size_t BACKGROUND_COLOR_B = 0xD5;
		static const size_t BACKGROUND_COLOR_OPAQUE = 0xFF;

	public:
		Config(std::string path);
		~Config() = default;
		size_t getWinHeight();
		size_t getWinWidth();
		size_t getMineCnt();
		size_t getFieldRowCnt();
		size_t getFieldColCnt();
		std::string getSpritePath();
		SDL_Rect* getClip(size_t type);

	private:
		size_t winHeight;
		size_t winWidth;
		size_t mineCnt;
		size_t fieldRowCnt;
		size_t fieldColCnt;
		std::string spritePath;
		std::map<size_t, SDL_Rect> clips;
		void loadConfig(std::string path);
		void loadClips(std::string path);
		int atoi(std::string str);
};

class Clip
{
	public:
		static const size_t DIGIT_0 = 0;
		static const size_t DIGIT_1 = 1;
		static const size_t DIGIT_2 = 2;
		static const size_t DIGIT_3 = 3;
		static const size_t DIGIT_4 = 4;
		static const size_t DIGIT_5 = 5;
		static const size_t DIGIT_6 = 6;
		static const size_t DIGIT_7 = 7;
		static const size_t DIGIT_8 = 8;
		static const size_t DIGIT_9 = 9;

		static const size_t SMILE_INIT = 10;
		static const size_t SMILE_PRESSED = 11;
		static const size_t SMILE_WONDER = 12;
		static const size_t SMILE_WIN = 13;
		static const size_t SMILE_LOSE = 14;

		static const size_t CELL_INIT = 15;
		static const size_t CELL_PRESSED = 16;
		static const size_t CELL_FLAG = 17;
		static const size_t CELL_FLAG_PRESSED = 18;
		static const size_t CELL_QM = 19;
		static const size_t CELL_QM_PRESSED = 20;
		static const size_t CELL_MINE = 21;
		static const size_t CELL_MINE_LOSE = 22;
		static const size_t CELL_MINE_WRONG = 23;

		static const size_t CELL_1 = 24;
		static const size_t CELL_2 = 25;
		static const size_t CELL_3 = 26;
		static const size_t CELL_4 = 27;
		static const size_t CELL_5 = 28;
		static const size_t CELL_6 = 29;
		static const size_t CELL_7 = 30;
		static const size_t CELL_8 = 31;
};

#endif
