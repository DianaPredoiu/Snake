#include "Game.h"
#include <Windows.h>
#include <thread>
#include <chrono>

Game::Game()
{
	working = init();
	loadTextures();
	inputHandler = new InputHandler();
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

void Game::displaySnake(GameMap &game, int multiplier)
{
	int multi = 40;
	int s = game.getSnake().getCoordinates().size() - 1;
	loadImage('T', gMap.getSnake().getCoordinates().at(s)->getX() *multi, gMap.getSnake().getCoordinates().at(s)->getY() *multi, -90);

	for (int i = game.getSnake().getCoordinates().size() - 2; i >= 0; --i)
	{
		if (i != 0)
		{
			if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX() + 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY())
			{
				loadImage('b', gMap.getSnake().getCoordinates().at(i)->getX() *multi, gMap.getSnake().getCoordinates().at(i)->getY() *multi, -90);
				//multi += 40;
			}
			else if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX() - 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY())
			{
				loadImage('b', gMap.getSnake().getCoordinates().at(i)->getX() *multi, gMap.getSnake().getCoordinates().at(i)->getY() *multi, 90);
				//multi += 40;
			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY() - 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX())
			{
				loadImage('b', gMap.getSnake().getCoordinates().at(i)->getX() *multi, gMap.getSnake().getCoordinates().at(i)->getY() *multi, 90);
				//multi += 40;
			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY() + 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX())
			{
				loadImage('b', gMap.getSnake().getCoordinates().at(i)->getX() *multi, gMap.getSnake().getCoordinates().at(i)->getY() * multi, 90);
				//multi += 40;
			}
		}
		else
		{
			if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX() - 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY())
			{
				loadImage('H', gMap.getSnake().getCoordinates().at(i)->getX() * multi, gMap.getSnake().getCoordinates().at(i)->getY() *multi, -90);
				//multi += 40;
			}
			else if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX() + 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY())
			{
				loadImage('H', gMap.getSnake().getCoordinates().at(i)->getX() * multi, gMap.getSnake().getCoordinates().at(i)->getY() *multi, 90);
				//multi += 40;
			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY() - 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX())
			{
				loadImage('H', gMap.getSnake().getCoordinates().at(i)->getX() *multi, gMap.getSnake().getCoordinates().at(i)->getY() * multi, 90);
				//multi += 40;
			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY() + 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX())
			{
				loadImage('H', gMap.getSnake().getCoordinates().at(i)->getX() *multi, gMap.getSnake().getCoordinates().at(i)->getY() *multi, 90);
				//multi += 40;
			}
		}
		
	}
	
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

std::string Game::direction(GameMap &game, std::string &xOrY)
{
	if (game.getSnake().getCoordinates().at(0)->getY() >= 0)
	{
		//body left->head => snake moves to right
		if (game.getSnake().getCoordinates().at(1)->getX() == (game.getSnake().getCoordinates().at(0)->getX() - 1))
		{
			xOrY = "+x";
			return "right";
		}

		//body right->head => snake moves to the left
		if (game.getSnake().getCoordinates().at(1)->getX() == (game.getSnake().getCoordinates().at(0)->getX() + 1))
		{
			xOrY = "-x";
			return "left";
		}
		//body up->head => snake moves down
		if (game.getSnake().getCoordinates().at(1)->getY() == (game.getSnake().getCoordinates().at(0)->getY() - 1))
		{
			xOrY = "+y";
			return "down";
		}

		//body down->head => snake moves up
		if (game.getSnake().getCoordinates().at(1)->getY() == (game.getSnake().getCoordinates().at(0)->getY() + 1))
		{
			xOrY = "-y";
			return "up";
		}

		//if (eatItself())
		//	return true;

	}
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
		int multiplier = 0;
		loadWindowWithBackground();
		displaySnake(game, multiplier);
		//working = true;
		inputHandler = new InputHandler();
		//std::thread t([&](){
		//	while (true)
		//	{
		//		SDL_RenderClear(renderer);
		//		loadWindowWithBackground();
		//		displaySnake(game, multiplier);
		//		Sleep(100);
		//	}
		//});

		while (working)
		{
			Sleep(100);
			SDL_Event e;
			e.key.keysym.sym = SDLK_UP;
			while (SDL_PollEvent(&e) != 0)
			{
				//std::cout << e.key.keysym.sym << std::endl;

				working = inputHandler->keyDown(e, game);
				multiplier += 40;
				SDL_RenderClear(renderer);
				loadWindowWithBackground();
				displaySnake(game, multiplier);
				
				

				//dir = direction(game, xOrY);
				//if (dir == "left" || dir == "up")
				//	multiplier = -20;
				//else if (dir == "right" || dir == "down")
				//{
				//	multiplier = 20;
				//}
				//else
				//{
				//	multiplier += 20;
				//}
				
				//displaySnake(game, multiplier);
				

				//displayGameDetails(game, positions);
				if (rules.isOutOfBounds() || working == false)
				{
					std::cout << "GAME OVER" << std::endl;
					working = false;
				}
			}

			if (!rules.continuousMovement())
			{
				multiplier += 40;
				//displayGameDetails(game, positions);
				SDL_RenderClear(renderer);
				loadWindowWithBackground();
				displaySnake(game, multiplier);
				//Sleep(100);
	/*			SDL_RenderClear(renderer);
				loadWindowWithBackground();*/
				//dir = direction(game, xOrY);
				//if (dir == "left" || dir == "up")
				//	multiplier -= 20;
				//else if (dir == "right" || dir == "down")
				//{
				//	multiplier += 20;
				//}
				//else
				//{
				//	multiplier += 20;
				//}
				
				//displaySnake(game, multiplier);

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
		/*t.join();*/
	}


	//delete ferestruica;
	//delete inputHandler;
	SDL_Quit();
}

bool Game::hasTheGameStarted()
{
	return init();
}
