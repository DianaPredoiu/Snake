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
	std::string path;


public:
	int h, w;
	Texture();
	void setPath(std::string path);

	void init();

	bool loadFromFile(std::string fileName, SDL_Renderer* renderer);	

	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer);

	bool loadFromRenderedTextWrapped(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer);

	SDL_Texture* GetTexture();

	~Texture();

};

