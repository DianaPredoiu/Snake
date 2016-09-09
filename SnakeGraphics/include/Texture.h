#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <fstream>
#include <cstdlib>

class Texture
{
public:
	Texture();
	~Texture();
	bool loadFromFile(std::string fileName, SDL_Renderer* renderer);
	bool loadFromRenderedText(std::string textTexture, SDL_Color textColor, TTF_Font* mFont, SDL_Renderer* renderer);
	void free();
	void render(int x, int y, SDL_Renderer* renderer);
	int getWidth() const;
	int getHeight() const;
	SDL_Texture* GetTexture();
	bool imgRect(SDL_Texture* texture, SDL_Renderer* renderer);

private:
	SDL_Texture *imTexture;
	int imWidth;
	int imHeight;
};

