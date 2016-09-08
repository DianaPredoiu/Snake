#include <iostream>
#include <theWindow.h>
#include "Main.h"
#include "Image_Loaders.h"

int main(int argc, char* argv[])
{
	bool quit = false;
	WindowSDL *ferestruica = new WindowSDL(&quit, 800, 600);
	
	while (quit == false && ferestruica->GetMainEvent()->type != SDL_QUIT)
	{
		ferestruica->Begin();
		//Game();
	
		
		ferestruica->End();
	}

	//delete ceva;
	//SDL_Quit();
	//Game();


	return 0;
}