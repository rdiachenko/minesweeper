#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>

//#define DEFAULT_CONF

#ifdef DEFAULT_CONF
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 286;
const std::string SPRITE_PATH = "sprites/classic.png";
#else
const int SCREEN_WIDTH = 780;
const int SCREEN_HEIGHT = 464;
const std::string SPRITE_PATH = "sprites/rd.png";
#endif

const int BACKGROUND_COLOR_R = 0xD5;
const int BACKGROUND_COLOR_G = 0xD5;
const int BACKGROUND_COLOR_B = 0xD5;
const int BACKGROUND_COLOR_OPAQUE = 0xFF;

#endif
