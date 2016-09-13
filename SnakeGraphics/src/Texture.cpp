#include "Texture.h"
#include <iostream>
#include "Presets.h"

Texture::Texture()
{
	
}

bool Texture::loadFromFile(std::string fileName, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = NULL;

	std::string p = FOO;

	// and attach the img folder to the project source path
	p.append("/sarpe/");
	p.append(fileName);


	//imTexture = IMG_LoadTexture(renderer, p.c_str());
	SDL_Surface* loadedSurface = IMG_Load(p.c_str());
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	if (newTexture == NULL)
	{
		std::cout << "Unable to create texture" << p.c_str() << ", SDL Error: " << SDL_GetError() << std::endl;
	}
	else
		imTexture = newTexture;

	SDL_FreeSurface(loadedSurface);
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