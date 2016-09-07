#include <iostream>
#include "SDL.h"

class WindowSDL{

public:
	WindowSDL(bool *quit, int ScreenWidth, int ScreenHeight);
	~WindowSDL();

	SDL_Renderer *GetRenderer();
	SDL_Event *GetMainEvent();

	void Begin();
	void End();

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event *mainEvent;


};