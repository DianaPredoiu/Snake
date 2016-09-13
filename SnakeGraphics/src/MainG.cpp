#include <iostream>
#include <theWindow.h>
#include "Main.h"
#include "Image_Loaders.h"
#include "Rules.h"
#include "GameMap.h"
#include "InputHandler.h"
#include "SDL.h"
#include "Texture.h"
#include "SymbolTranslation.h"

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
SDL_Surface* screenSurface = NULL;

SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;





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
		std::cout << "Failed to initialize!\n" << std::endl;
	}
	else
	{
		LoadWindowWithBackground();
		bool working = true;
		inputHandler = new InputHandler();
		while (working)
		{
			
			SymbolTranslation* capSym = new SymbolTranslation('T', renderer);
			capSym->ConvertToTextureFromSymbol();

			//SDL_RenderCopy(renderer, capSym->GetTexture().GetTexture(), NULL, NULL);


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

	}


	//delete ferestruica;
	//delete inputHandler;
	SDL_Quit();
	return 0;
}