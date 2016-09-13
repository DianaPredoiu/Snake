#include "Texture.h"
#include <iostream>
#include "Presets.h"

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

bool Texture::loadFromFile(std::string fileName, SDL_Renderer* renderer, int width, int height)
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
		newTexture = IMG_LoadTexture(renderer, p.c_str());
		int a, b;
		SDL_QueryTexture(newTexture, NULL, NULL, &a, &b);
		//newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_Rect texr; texr.x = 150; texr.y = 150; texr.w = a / 10; texr.h = b / 10;
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture" << p.c_str() << ", SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			//imWidth = width;
			//imHeight = height;
		}

		SDL_FreeSurface(loadedSurface);
		//SDL_RenderClear(renderer);
		SDL_Point p;
		p.x = texr.x / 2;
		p.y = texr.y / 2;
		SDL_RenderCopyEx(renderer, newTexture, NULL, &texr, -90, &p, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		SDL_RenderPresent(renderer);
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

SDL_Rect Texture::imgRect(SDL_Texture* texture, SDL_Renderer* renderer, int ulcposX, int ulcposY, int squareMeasure)
{
	SDL_Rect imgRectangle;


	SDL_QueryTexture(texture, nullptr, nullptr, &imgRectangle.w, &imgRectangle.h);
	imgRectangle.x = 50;
	imgRectangle.y = 50;
	imgRectangle.w = 1;
	imgRectangle.h = 1;
	SDL_Rect texr; texr.x = 600 / 2; texr.y = 600 / 2; texr.w = imgRectangle.w / 2; texr.h = imgRectangle.h / 2;

	//SDL_BlitScaled(renderer, NULL, texture, &imgRectangle);
	//SDL_RenderCopyEx(renderer, texture, NULL, &imgRectangle, NULL, NULL, SDL_FLIP_NONE);
	//SDL_RenderFillRect(renderer, &imgRectangle);
	return imgRectangle;
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