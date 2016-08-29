#include <iostream>
#include <SDL2/SDL_image.h>
#include "Texture.h"

Texture::Texture(SDL_Renderer* const renderer, std::string path) : texture(nullptr)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	
	if (surface == nullptr)
	{
		std::cerr << "Can't load image " << path << ": " << IMG_GetError() << '\n';
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		
		if (texture == nullptr)
		{
			std::cerr << "Can't create texture from " << path << ": " << SDL_GetError() << '\n';
		}
		SDL_FreeSurface(surface);
	}
}

Texture::~Texture()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Texture::render(int x, int y, const SDL_Rect* const clip, SDL_Renderer* const renderer)
{
	SDL_Rect rect = {x, y, clip->w, clip->h};
	SDL_RenderCopy(renderer, texture, clip, &rect);
}
