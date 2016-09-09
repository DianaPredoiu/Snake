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
		SDL_RenderCopy(ferestruica->GetRenderer(), ferestruica->GetTexture(), NULL, NULL);
		SDL_RenderPresent(ferestruica->GetRenderer());
	
		IMTexture* tex = new IMTexture(ferestruica->GetRenderer(), "cap.bmp", 50, 50);

		SDL_RenderCopy(ferestruica->GetRenderer(), tex->GetTexture(), NULL, NULL);
		SDL_RenderPresent(ferestruica->GetRenderer());

		
		ferestruica->End();
	}

	delete ferestruica;
	SDL_Quit();
	return 0;
}