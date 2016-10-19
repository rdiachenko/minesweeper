#include <fstream>
#include <iostream>
#include <cctype>
#include "Config.h"

static const size_t LIMIT = 1000;

Config::Config(std::string path)
{
	loadConfig(path);
}

size_t Config::getWinHeight()
{
	return winHeight;
}

size_t Config::getWinWidth()
{
	return winWidth;
}

size_t Config::getMineCnt()
{
	return mineCnt;
}

size_t Config::getFieldRowCnt()
{
	return fieldRowCnt;
}

size_t Config::getFieldColCnt()
{
	return fieldColCnt;
}

std::string Config::getSpritePath()
{
	return spritePath;
}

SDL_Rect* Config::getClip(size_t type)
{
	return &clips[type];
}

void Config::loadConfig(std::string path)
{
	std::ifstream in(path);

	if (in.is_open())
	{
		std::string line;

		while (getline(in, line) && !line.empty())
		{
			std::string key;
			std::string value;
			size_t index = 0;
			
			while (index < line.size() && line[index] != '=')
			{
				if (!isspace(line[index])) key.push_back(line[index]);
				index++;
			}

			index++; // skip '='

			while (index < line.size())
			{
				if (!isspace(line[index])) value.push_back(line[index]);
				index++;
			}

			if (key == "mines")
			{
				mineCnt = atoi(value);
			}
			else if (key == "field_rows")
			{
				fieldRowCnt = atoi(value);
			}
			else if (key == "field_cols")
			{
				fieldColCnt = atoi(value);
			}
			else if (key == "sprite_img")
			{
				spritePath = value;
			}
			else if (key == "sprite_txt")
			{
				loadClips(value);
			}
			else
			{
				std::cout << "WARN: unknown property: " << key << std::endl;
			}
		}
		if (fieldRowCnt > 0 && fieldRowCnt < LIMIT && fieldColCnt > 0 && fieldColCnt < LIMIT)
		{
			size_t dim = fieldRowCnt * fieldColCnt;

			if (mineCnt >= dim)
			{
				size_t defaultMineCnt = dim / 2;
				std::cout << "WARN: too many mines: " << mineCnt << ". Default value will be used: " << defaultMineCnt << std::endl;
				mineCnt = defaultMineCnt;
			}
			winHeight = 2 + getClip(Clip::SMILE_INIT)->h + 2 + fieldRowCnt * getClip(Clip::CELL_INIT)->h;
			winWidth = fieldColCnt * getClip(Clip::CELL_INIT)->w;
		}
		else
		{
			std::cerr << "Unsupported rows/columns count: rows=" << fieldRowCnt << ", columns=" << fieldColCnt << ". Max value for rows=" << LIMIT << ", columns=" << LIMIT << std::endl;
		}
	}
	else
	{
		std::cerr << "Failed to open file: " << path << std::endl;
	}
}

void Config::loadClips(std::string path)
{
	std::ifstream in(path);

	if (in.is_open())
	{
		std::string line;
		size_t clipCnt = 0;

		while (getline(in, line) && !line.empty())
		{
			size_t n = 4;
			std::string rect[n];
			size_t rectIndex = 0;
			size_t index = 0;

			while (index < line.size() && line[index] != '#')
			{
				if (isdigit(line[index]))
				{
					rect[rectIndex].push_back(line[index]);
				}
				else if (isspace(line[index]))
				{
					rectIndex++;
				}
				index++;
			}
			if (rectIndex >= n - 1)
			{
				clips[clipCnt] = {atoi(rect[0]), atoi(rect[1]), atoi(rect[2]), atoi(rect[3])};
				clipCnt++;
			}
		}
	}
	else
	{
		std::cerr << "Failed to open file: " << path << std::endl;
	}
}

int Config::atoi(std::string str)
{
	int val = 0;

	for (const auto& ch : str)
	{
		if (isdigit(ch))
		{
			val *= 10;
			val += (ch - '0');
		}
	}
	return val;
}
