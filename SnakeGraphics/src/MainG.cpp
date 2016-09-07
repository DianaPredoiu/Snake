#include <iostream>
#include <theWindow.h>
#include "Main.h"

int main(int argc, char* argv[])
{
	bool quit = false;
	WindowSDL *ceva = new WindowSDL(&quit, 800, 600);
	while (quit == false && ceva->GetMainEvent()->type != SDL_QUIT)
	{
		ceva->Begin();
		// fara obiecte create in acest while
		// game code
		Game();
		ceva->End();
	}

	delete ceva;
	SDL_Quit();

	return 0;
}