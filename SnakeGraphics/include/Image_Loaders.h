#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class IMTexture
{
public:
	//Initializes variables
	IMTexture(SDL_Renderer *requiredRenderer, std::string fileName, int width, int height);

	IMTexture()
	{
		imHeight = 0;
		imWidth = 0;
		imTexture = NULL;
	}

	//Deallocates memory
	~IMTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Gets image dimensions
	int getWidth();
	int getHeight();

	SDL_Texture GetTexture();

private:
	//The actual hardware texture
	SDL_Texture* imTexture;
//	WindowSDL *window = new WindowSDL(false, 800, 600);

	//Image dimensions
	int imWidth;
	int imHeight;
};