#include "Texture.h"
#include <iostream>
#include "Presets.h"

Texture::Texture()
{

}

bool Texture::loadFromFile(std::string fileName, SDL_Renderer* renderer)
{
	imTexture = NULL;

	std::string p = FOO;

	// and attach the img folder to the project source path
	p.append("/sarpe/");
	p.append(fileName);


	imTexture = IMG_LoadTexture(renderer, p.c_str());

	int a, b;
	SDL_QueryTexture(imTexture, NULL, NULL, &a, &b);

	SDL_Rect rectangle;

	rectangle.x = 50;
	rectangle.y = 50;
	rectangle.w = a / 10;
	rectangle.h = b / 10;

	if (imTexture == NULL)
	{
		std::cout << "Unable to create texture" << p.c_str() << ", SDL Error: " << SDL_GetError() << std::endl;
	}


	//SDL_Point p;
	//p.x = rectangle.x / 2;
	//p.y = rectangle.y / 2;
	//SDL_RenderCopyEx(renderer, newTexture, NULL, &texr, -90, &p, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
	//SDL_RenderPresent(renderer);

	return imTexture != NULL;
}


SDL_Texture* Texture::GetTexture()
{
	return imTexture;
}

Texture::~Texture()
{

}