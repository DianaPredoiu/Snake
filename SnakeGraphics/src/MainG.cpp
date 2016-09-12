#include <iostream>
#include <theWindow.h>
#include "Main.h"
#include "Image_Loaders.h"
<<<<<<< HEAD
#include "Rules.h"
#include "GameMap.h"
#include "InputHandler.h"
#include "SDL.h"

void displayGameDetails(GameMap &game, std::vector<Position*> pos)
{
	Sleep(300);
	system("cls");

	game.initializeGrid(pos);
	std::cout << game;
	std::cout << std::endl << std::endl << "---Score: " << game.getScore() << "  ---" << std::endl << std::endl;

	if (game.getBonus().getState() == true)
		std::cout << "---Bonus Time: " << game.getBonus().getTime() << "  ---" << std::endl << std::endl;

	if (game.getSurprise().getState() == true)
	{
		std::cout << "---Surprise Time: " << game.getSurprise().getTime() << "  ---" << std::endl << std::endl;
		std::cout << std::endl << "---Effect: " << game.getSurprise().getEffect() << "  ---";
	}
}

SDL_Window *ferestruica = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		ferestruica = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 300, SDL_WINDOW_SHOWN);
		if (ferestruica == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(ferestruica);
		}
	}

	return success;
}
=======
#include "Texture.h"
<<<<<<< HEAD
#include "SymbolTranslation.h"
=======
>>>>>>> origin/master
>>>>>>> origin/master

int main(int argc, char* argv[])
{
	bool quit = false;
	

	GameMap game(15, 15);
	Rules rules(&game);
	InputHandler *inputHandler;

	std::cout << game;
	std::vector<Position*> positions = game.initializeGrid(game.getSnake().getCoordinates());

	game.setScore(0);

	if (!init())
	{
<<<<<<< HEAD
		std::cout<<"Failed to initialize!\n"<<std::endl;
	}
	else
	{
		bool working = true;
		inputHandler = new InputHandler();
		while (working)
		{
			/*ferestruica->Begin();

			SDL_RenderCopy(ferestruica->GetRenderer(), ferestruica->GetTexture(), NULL, NULL);
			SDL_RenderPresent(ferestruica->GetRenderer());*/
			//Game();

			SDL_Event e;		
			while (SDL_PollEvent(&e) != 0)
			{
				working = inputHandler->keyDown(e, game);
				
				displayGameDetails(game, positions);
				if (rules.isOutOfBounds() || working == false)
				{
					std::cout << "GAME OVER" << std::endl;
					working = false;
				}
			}

			if (!rules.continuousMovement())
			{
				displayGameDetails(game, positions);
				if (rules.isOutOfBounds())
				{
					std::cout << "GAME OVER!" << std::endl;
					break;
				}
			}
			else
			{
				std::cout << "GAME OVER!" << std::endl;
				break;
			}


			//ferestruica->End();
		}
=======
		ferestruica->Begin();
		//Game();
		SDL_RenderCopy(ferestruica->GetRenderer(), ferestruica->GetTexture(), NULL, NULL);
		SDL_RenderPresent(ferestruica->GetRenderer());
	
		/*IMTexture* tex = new IMTexture(ferestruica->GetRenderer(), "cap.bmp", 50, 50);

		SDL_RenderCopy(ferestruica->GetRenderer(), tex->GetTexture(), NULL, NULL);
		SDL_RenderPresent(ferestruica->GetRenderer());
*/

		Texture tex;

		tex.loadFromFile("cap.bmp", ferestruica->GetRenderer(), 100, 100);
		SDL_Rect texRect = tex.imgRect(tex.GetTexture(), ferestruica->GetRenderer());
		
		SymbolTranslation* capSym = new SymbolTranslation('T', ferestruica->GetRenderer());
		capSym->ConvertToTextureFromSymbol();

		SDL_RenderCopy(ferestruica->GetRenderer(), capSym->GetTexture().GetTexture(), &texRect, NULL);
		SDL_RenderPresent(ferestruica->GetRenderer());

		ferestruica->End();
>>>>>>> origin/master
	}
	

	//delete ferestruica;
	//delete inputHandler;
	SDL_Quit();
	return 0;
}