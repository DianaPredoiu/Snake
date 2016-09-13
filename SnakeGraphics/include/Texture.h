#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <fstream>
#include <cstdlib>

class Texture
{
	SDL_Texture *imTexture;

public:
	Texture();

	bool loadFromFile(std::string fileName, SDL_Renderer* renderer);

	SDL_Texture* GetTexture();

	~Texture();

};

