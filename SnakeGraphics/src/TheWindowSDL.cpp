#include "theWindow.h"
#include <iostream>
#include <Image_Loaders.h>
#include <windows.h>
#include <string>
#include <tchar.h>
#include <stdio.h>




WindowSDL::WindowSDL(bool *quit, int ScreenWidth, int ScreenHeight)
{
	SDL_Init(SDL_INIT_VIDEO);

	window = NULL;
	window = SDL_CreateWindow("Just Another Snake Game", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window not defined";
		*quit = true;
	}
	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// get the path to the img source folder
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/grass.bmp");
	// load img and print on window
	screenSurface = SDL_LoadBMP(p.c_str());

	if (!screenSurface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
	}

	texture = SDL_CreateTextureFromSurface(renderer, screenSurface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
	}
	
	SDL_FreeSurface(screenSurface);

	//SDL_UpdateWindowSurface(window);

	mainEvent = new SDL_Event;
}




WindowSDL::~WindowSDL(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer *WindowSDL::GetRenderer()
{
	return renderer;
}
SDL_Event *WindowSDL::GetMainEvent()
{
	return mainEvent;
}

void WindowSDL::Begin()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);

}
void WindowSDL::End(){
	SDL_RenderPresent(renderer);
}

void WindowSDL::SetTexture(SDL_Texture *tex)
{
	texture = tex;
}

void WindowSDL::SetSurface(SDL_Surface *surface)
{
	screenSurface = surface;
}

void WindowSDL::loadSurface(std::string path)
{
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load("../sarpe/grass.bmp");
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image! SDL_image Error:\n" << path.c_str() << " " << IMG_GetError();
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from! SDL Error:\n" << path.c_str() << " " << SDL_GetError();
		}
		
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}	
}

SDL_Texture* WindowSDL::GetTexture()
{
	return this->texture;
}