#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

class Texture
{
	public:
		Texture(SDL_Renderer* const renderer, std::string path);
		~Texture();
		void render(int x, int y, const SDL_Rect* const clip, SDL_Renderer* const renderer);

	private:
		SDL_Texture* texture;
};

#endif
