#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cstdio>
#include <Image_Loaders.h>


// LTexture
IMTexture::IMTexture(SDL_Renderer *requiredRenderer, std::string fileName, int width, int height)
{
	//Initialize
	imTexture = IMG_LoadTexture(requiredRenderer, fileName.c_str());
	imWidth = width;
	imHeight = height;
}

IMTexture::~IMTexture()
{
	//Deallocate
	free();
}

bool IMTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	//free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load("../sarpe/grass.png");
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error:\n" << path.c_str() << " " << IMG_GetError();
	}
	else
	{
		//Create texture from surface pixels
//		newTexture = SDL_CreateTextureFromSurface(window->GetRenderer(), loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from! SDL Error:\n" << path.c_str() << " " << SDL_GetError();
		}
		else
		{
			//Get image dimensions
			imWidth = loadedSurface->w;
			imHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	imTexture = newTexture;
	return imTexture != NULL;
}


void IMTexture::free()
{
	//Free texture if it exists
	if (imTexture != NULL)
	{
		SDL_DestroyTexture(imTexture);
		imTexture = NULL;
		imWidth = 0;
		imHeight = 0;
	}
}

