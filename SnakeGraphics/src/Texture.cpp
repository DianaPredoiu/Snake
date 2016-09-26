#include "Texture.h"
#include <iostream>
#include "Presets.h"

Texture::Texture()
{
	path = FOO;
	path.append("/sarpe/font.ttf");
}

void Texture::setPath(std::string path)
{
	this->path = FOO;
	this->path.append(path);
}

void Texture::init()
{
	if (TTF_Init())
	{
		std::cout << "TTF INIT ERROR" << std::endl;
		return;
	}
	else
	{

		font = TTF_OpenFont(path.c_str(), 30);
	}
}

bool Texture::loadFromFile(std::string fileName, SDL_Renderer* renderer)
{
	imTexture = NULL;
	SDL_Texture* newTexture = NULL;

	std::string p = FOO;

	// and attach the img folder to the project source path
	p.append("/sarpe/");
	p.append(fileName);


	SDL_Surface* loadedSurface = IMG_Load(p.c_str());
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	if (newTexture == NULL)
	{
		std::cout << "Unable to create texture" << p.c_str() << ", SDL Error: " << SDL_GetError() << std::endl;
	}
	else
		imTexture = newTexture;

	SDL_FreeSurface(loadedSurface);
	newTexture = NULL;

	return imTexture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer)
{
	//Render text surface
	if (!font)
	{
		std::cout << "Unable to load font style! SDL_TTF Error: \n" << TTF_GetError();
	}
	else
	{
		init();
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
		h = textSurface->h;
		w = textSurface->w;
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

		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	return imTexture != NULL;
}

bool Texture::loadFromRenderedTextWrapped(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer)
{
	//Render text surface
	if (!font)
	{
		std::cout << "Unable to load font style! SDL_TTF Error: \n" << TTF_GetError();
	}
	else
	{
		init();
		SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 300);
		h = textSurface->h;
		w = textSurface->w;
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


		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	return imTexture != NULL;
}

SDL_Texture* Texture::GetTexture()
{
	return imTexture;
}

Texture::~Texture()
{
	TTF_CloseFont(font);
}