#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <fstream>
#include <cstdlib>

class Texture
{
	SDL_Texture *imTexture;
	TTF_Font *font;

public:
	Texture();

	bool loadFromFile(std::string fileName, SDL_Renderer* renderer);

	bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer);

	SDL_Texture* GetTexture();

	~Texture();

};

