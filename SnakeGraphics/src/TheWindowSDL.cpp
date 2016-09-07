#include "theWindow.h"
#include <iostream>

WindowSDL::WindowSDL(bool *quit, int ScreenWidth, int ScreenHeight)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	window = NULL;
	window = SDL_CreateWindow("o fereastra QFort", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window not defined";
		*quit = true;
	}
	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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