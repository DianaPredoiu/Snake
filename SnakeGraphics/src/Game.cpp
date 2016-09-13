#include "Game.h"

Game::Game()
{
	init();
	loadTextures();
}

void Game::loadWindowWithBackground()
{
	SDL_RenderClear(renderer);
	// get the path to the img source folder
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/grass.png");
	// load img and print on window
	background = IMG_LoadTexture(renderer, p.c_str());

	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderPresent(renderer);
}

// using the class that converts from a given symbol to a specific 
// texture we load a map of textures for the game
void Game::loadTextures()
{
	SymbolTranslation* capSym = new SymbolTranslation('H', renderer);
	textures["head"] = capSym->ConvertToTextureFromSymbol();

	SymbolTranslation* bodySym = new SymbolTranslation('b', renderer);
	textures["body"] = bodySym->ConvertToTextureFromSymbol();

	SymbolTranslation* tailSym = new SymbolTranslation('T', renderer);
	textures["tail"] = tailSym->ConvertToTextureFromSymbol();

	SymbolTranslation* foodSym = new SymbolTranslation('F', renderer);
	textures["food"] = foodSym->ConvertToTextureFromSymbol();

	SymbolTranslation* bonusSym = new SymbolTranslation('B', renderer);
	textures["bonus"] = bonusSym->ConvertToTextureFromSymbol();

	SymbolTranslation* surpriseSym = new SymbolTranslation('?', renderer);
	textures["surprise"] = surpriseSym->ConvertToTextureFromSymbol();
}

bool Game::init()
{
	screenSurface = NULL;
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: \n" << SDL_GetError();
		success = false;
	}
	else
	{
		//Create window and renderer
		window = SDL_CreateWindow("El Snake Roho", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL Error: \n" << SDL_GetError();
			success = false;
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return success;
}

Game::~Game()
{
	SDL_RenderPresent(renderer);
}

void Game::executeGame()
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
}

bool Game::hasTheGameStarted()
{
	return init();
}

void Game::render()
{

}

void Game::gameLogic()
{

}

void Game::updateMove()
{

}

void Game::checkCollision()
{

}