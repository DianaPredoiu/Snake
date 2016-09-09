#include "Texture.h"
#include <iostream>

Texture::Texture()
{
	imTexture = 0;
	imWidth = 0;
	imHeight = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(std::string fileName, SDL_Renderer* renderer)
{
	// empty the surface to make sure it doesn't collide in textures
	free();

	SDL_Texture* newTexture = NULL;
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/");
	p.append(fileName);
	// load img and print on window
	SDL_Surface* loadedSurface = IMG_Load(p.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load the image " << p.c_str() << ", SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture" << p.c_str() << ", SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			imWidth = loadedSurface->w;
			imHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	imTexture = newTexture;
	return imTexture != NULL;
}

bool Texture::loadFromRenderedText(std::string textTexture, SDL_Color textColor, TTF_Font* mFont, SDL_Renderer* renderer)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, textTexture.c_str(), textColor);
	if (textSurface == NULL)
	{
		std::cout << "Unable to render text, SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		imTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (imTexture == NULL)
		{
			std::cout << "Unable to create texture from text, SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			imWidth = textSurface->w;
			imHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return imTexture != NULL;
}

void Texture::free()
{
	if (imTexture == NULL)
	{
		SDL_DestroyTexture(imTexture);
		imTexture = NULL;
		imWidth = 0;
		imHeight = 0;
	}
}

void Texture::render(int x, int y, SDL_Renderer *renderer)
{
	SDL_Rect renderQuad = { x, y, imWidth, imHeight };

	SDL_RenderCopy(renderer, imTexture, NULL, &renderQuad);
}

int Texture::getWidth() const
{
	return imWidth;
}

int Texture::getHeight() const
{
	return imHeight;
}


SDL_Texture* Texture::GetTexture()
{
	return imTexture;
}