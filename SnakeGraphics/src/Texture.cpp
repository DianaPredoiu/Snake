#include "Texture.h"
#include <iostream>
#include "Presets.h"


Texture::Texture()
{
	TTF_Init();
	std::string p = FOO;
	p.append("/sarpe/font.ttf");
	font = TTF_OpenFont(p.c_str(), 28);
}

bool Texture::loadFromFile(std::string fileName, SDL_Renderer* renderer)
{
	imTexture = NULL;
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
	
	//SDL_RenderCopyEx(renderer, newTexture, NULL, &texr, -90, &p, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
	//SDL_RenderPresent(renderer);

	return imTexture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer)
{
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "ceva in mijloc", textColor);
	if (textSurface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: \n" << TTF_GetError();
	}
	else
	{
		//Create texture from surface pixels
		imTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (imTexture == NULL)
		{
			std::cout << "Unable to create texture from rendered text! SDL Error: \n" << SDL_GetError();
		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return imTexture != NULL;
}


SDL_Texture* Texture::GetTexture()
{
	return imTexture;
}

Texture::~Texture()
{

}