#include "Game.h"

Game::Game()
{
	working = init();
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
	capSym->ConvertToTextureFromSymbol();
	textures['H'] = capSym->GetTexture();

	SymbolTranslation* bodySym = new SymbolTranslation('b', renderer);
	bodySym->ConvertToTextureFromSymbol();
	textures['b'] = bodySym->GetTexture();

	SymbolTranslation* tailSym = new SymbolTranslation('T', renderer);
	tailSym->ConvertToTextureFromSymbol();
	textures['T'] = tailSym->GetTexture();

	SymbolTranslation* foodSym = new SymbolTranslation('F', renderer);
	foodSym->ConvertToTextureFromSymbol();
	textures['F'] = foodSym->GetTexture();

	SymbolTranslation* bonusSym = new SymbolTranslation('B', renderer);
	bonusSym->ConvertToTextureFromSymbol();
	textures['B'] = bonusSym->GetTexture();

	SymbolTranslation* surpriseSym = new SymbolTranslation('?', renderer);
	surpriseSym->ConvertToTextureFromSymbol();
	textures['?'] = surpriseSym->GetTexture();

}

void Game::displaySnake()
{
	int multiplier = 1;
	int s = gMap.getSnake().getCoordinates().size() - 1;
	loadImage('T', gMap.getSnake().getCoordinates().at(s)->getX(), gMap.getSnake().getCoordinates().at(s)->getY(), -90);
	for (int i = gMap.getSnake().getCoordinates().size() - 2; i >= 1 ; --i)
	{
		loadImage('b', gMap.getSnake().getCoordinates().at(i)->getX() + 40 * multiplier, gMap.getSnake().getCoordinates().at(i)->getY(), 0);
		multiplier++;
	}
	loadImage('H', gMap.getSnake().getCoordinates().at(0)->getX() + 40 * multiplier, gMap.getSnake().getCoordinates().at(0)->getY(), -90);
}

void Game::loadImage(char textureName, int x, int y, int angle)
{
	SDL_Rect rectangle;

	int a, b;
	SDL_QueryTexture(textures[textureName], NULL, NULL, &a, &b);

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = a / 10;
	rectangle.h = b / 10;

	SDL_RenderCopyEx(renderer, textures[textureName], NULL, &rectangle, angle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
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
	GameMap game(15, 15);
	Rules rules(&game);
	InputHandler *inputHandler;

	//std::cout << game;
	std::vector<Position*> positions = game.initializeGrid(game.getSnake().getCoordinates());

	game.setScore(0);

	if (!working)
	{
		std::cout << "Failed to initialize!\n" << std::endl;
	}
	else
	{
		loadWindowWithBackground();
		displaySnake();
		//working = true;
		inputHandler = new InputHandler();
		while (working)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				working = inputHandler->keyDown(e, game);
				displaySnake();
				//displayGameDetails(game, positions);
				if (rules.isOutOfBounds() || working == false)
				{
					std::cout << "GAME OVER" << std::endl;
					working = false;
				}
			}

			if (!rules.continuousMovement())
			{
				//displayGameDetails(game, positions);
				//displaySnake();
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
