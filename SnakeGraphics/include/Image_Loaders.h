#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


class IMTexture
{
public:
	//Initializes variables
	IMTexture();

	//Deallocates memory
	~IMTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* imTexture;

	//Image dimensions
	int imWidth;
	int imHeight;
};