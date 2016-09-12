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
	imTexture = loadFromFile(fileName);
	imWidth = width;
	imHeight = height;
	renderer = requiredRenderer;
}

IMTexture::~IMTexture()
{
	//Deallocate
	free();
}

SDL_Texture* IMTexture::loadFromFile(std::string fileName)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	// Get the path to the img source folder
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/");
	p.append(fileName);
	// load img and print on window
	SDL_Surface* loadedSurface = IMG_Load(p.c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error:\n" << p.c_str() << " " << IMG_GetError();
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from! SDL Error:\n" << p.c_str() << " " << SDL_GetError();
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
	return imTexture;
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

SDL_Texture* IMTexture::GetTexture()
{
	return imTexture;
}

int IMTexture::getHeight()
{
	return imHeight;
}

int IMTexture::getWidth()
{
	return imWidth;
}

void IMTexture::DrawImage(SDL_Surface *surface, char *image_path, int x_pos, int y_pos)
{
	SDL_Surface *image = IMG_Load(image_path);
	if (!image)
	{
		std::cout << "IMG_Load:\n" << IMG_GetError();
	}

	// Draws the image on the screen:
	SDL_Rect rcDest = { x_pos, y_pos, 0, 0 };
	SDL_BlitSurface(image, NULL, surface, &rcDest);

	//SDL_UpdateRect(surface, x_pos, y_pos, image->w, image->h); 

	SDL_FreeSurface(image);
}