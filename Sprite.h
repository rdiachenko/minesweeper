#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL2/SDL.h>

extern const int CLIPS_COUNT;
extern const SDL_Rect clips[];

class Sprite
{
	public:
		SDL_Rect getClip(int type);
};

#endif
