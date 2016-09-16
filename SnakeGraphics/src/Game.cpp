#include "Game.h"
#include <Windows.h>
#include "Presets.h"

Game::Game()
{
	working = init();
	loadTextures();

	delay = 100;

	inputHandler = new InputHandler();

	bgColor = { 238, 238, 0 };
	textColor = { 0, 0, 0 };
	textRectangle.h = 50;
	textRectangle.w = 600;
	textRectangle.x = 0;
	textRectangle.y = 750;

	step = SCREEN_WIDTH / 15;

	textTexture.init();
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
		window = SDL_CreateWindow("El Snake Roho", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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


#pragma region display items + snake + details
void Game::displayFood(int x, int y)
{
	printImage('F', x * step, y * step, 0);
}

void Game::displayBonus(int x, int y)
{
	printImage('B', x * step, y * step, 0);
	if (delay != 70)
		delay = 70;
	else
		delay = 50;
}

void Game::displaySurprise(int x, int y)
{
	printImage('?', x * step, y * step, 0);
}

void Game::displaySnake(GameMap &game)
{
	int s = game.getSnake().getCoordinates().size() - 1;
	printImage('T', game.getSnake().getCoordinates().at(s)->getX() * step, game.getSnake().getCoordinates().at(s)->getY() * step, tailDirection(game));

	for (int i = game.getSnake().getCoordinates().size() - 2; i >= 0; i--)
	{
		//std::cout << game.getSnake().getCoordinates().at(i)->getX() << " " << game.getSnake().getCoordinates().at(i)->getY() << std::endl;
		if (i != 0)
		{

			if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX() + 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step, game.getSnake().getCoordinates().at(i)->getY() *step, -90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX() - 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step, game.getSnake().getCoordinates().at(i)->getY() *step, 90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY() - 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step, game.getSnake().getCoordinates().at(i)->getY() *step, 90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY() + 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step, game.getSnake().getCoordinates().at(i)->getY() * step, 90);

			}
		}
		else
		{
			if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX() - 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() * step, game.getSnake().getCoordinates().at(i)->getY() *step, 90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX() + 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() * step, game.getSnake().getCoordinates().at(i)->getY() *step, -90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY() - 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() *step, game.getSnake().getCoordinates().at(i)->getY() * step, 180);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY() + 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() *step, game.getSnake().getCoordinates().at(i)->getY() *step, 0);

			}
		}

	}

	game.addFood();
	displayFood(game.getFood().getCoordinates().getX(), game.getFood().getCoordinates().getY());
	if (game.getBonus().getState())
	{
		displayBonus(game.getBonus().getCoordinates().getX(), game.getBonus().getCoordinates().getY());
	}

	if (game.getSurprise().getState())
	{
		displaySurprise(game.getSurprise().getCoordinates().getX(), game.getSurprise().getCoordinates().getY());
	}

}


void Game::displayGameDetails(GameMap &game, std::vector<Position*> pos)
{
	game.initializeGrid(pos);
	//std::cout << game;
	//std::cout << std::endl << std::endl << "---Score: " << game.getScore() << "  ---" << std::endl << std::endl;

	//if (game.getBonus().getState() == true)
	//	std::cout << "---Bonus Time: " << game.getBonus().getTime() << "  ---" << std::endl << std::endl;

	//if (game.getSurprise().getState() == true)
	//{
	//	std::cout << "---Surprise Time: " << game.getSurprise().getTime() << "  ---" << std::endl << std::endl;
	//	std::cout << std::endl << "---Effect: " << game.getSurprise().getEffect() << "  ---";
	//}
	//SDL_Surface *rectangleSurface;
	//rectangleSurface = SDL_CreateRGBSurface(0, 750, 50, 32, 0, 0, 0, 0);

	///* Filling the surface with red color. */
	//SDL_FillRect(rectangleSurface, NULL, SDL_MapRGB(rectangleSurface->format, 255, 0, 0));

	////textTexture.loadFromRenderedText("TEXT! TEXT! TEXT! TEXT! TEXT! TEXT! TEXT! TEXT! TEXT! ", textColor, renderer);
	//SDL_RenderCopy(renderer, textTexture.GetTexture(), NULL, &textRectangle);
	//SDL_RenderPresent(renderer);
}
#pragma endregion

int Game::tailDirection(GameMap &game)
{
	int size = game.getSnake().getCoordinates().size();
	if (game.getSnake().getCoordinates().at(size - 1)->getX() == game.getSnake().getCoordinates().at(size - 2)->getX() - 1
		&& game.getSnake().getCoordinates().at(size - 1)->getY() == game.getSnake().getCoordinates().at(size - 2)->getY())
	{
		return -90;
	}
	else if (game.getSnake().getCoordinates().at(size - 1)->getX() == game.getSnake().getCoordinates().at(size - 2)->getX() + 1
		&& game.getSnake().getCoordinates().at(size - 1)->getY() == game.getSnake().getCoordinates().at(size - 2)->getY())
	{
		return 90;
	}
	else if (game.getSnake().getCoordinates().at(size - 1)->getY() == game.getSnake().getCoordinates().at(size - 2)->getY() - 1
		&& game.getSnake().getCoordinates().at(size - 1)->getX() == game.getSnake().getCoordinates().at(size - 2)->getX())
	{
		return 0;
	}
	else if (game.getSnake().getCoordinates().at(size - 1)->getY() == game.getSnake().getCoordinates().at(size - 2)->getY() + 1
		&& game.getSnake().getCoordinates().at(size - 1)->getX() == game.getSnake().getCoordinates().at(size - 2)->getX())
	{
		return 180;
	}
}

void Game::printImage(char textureName, int x, int y, int angle)
{
	SDL_Rect rectangle;

	int a, b;
	SDL_QueryTexture(textures[textureName], NULL, NULL, &a, &b);

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = 40;
	rectangle.h = 40;

	SDL_RenderCopyEx(renderer, textures[textureName], NULL, &rectangle, angle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
}

#pragma region Execution
void Game::executeGame()
{
	GameMap game(15, 15);
	Rules rules(&game);
	InputHandler *inputHandler;

	std::vector<Position*> positions = game.initializeGrid(game.getSnake().getCoordinates());

	game.setScore(0);

	if (!working)
	{
		std::cout << "Failed to initialize!\n" << std::endl;
	}
	else
	{
		loadWindowWithBackground();
		displaySnake(game);
		displayGameDetails(game, positions);
		inputHandler = new InputHandler();


		int frame = 0;

		bool capFrameRate = true;
		// the frame rate handler
		Timer fpsTimer;

		//The frames persecond cap timer
		Timer capTimer;
		int lastUpdateTime = 0;
		int countedFrames = 0;
		int currentTime = SDL_GetTicks();
		int delta_time = currentTime - lastUpdateTime * 10;

		while (working)
		{
			SDL_Event e;
			e.key.keysym.sym = SDLK_UP;
			capTimer.start();
			while (SDL_PollEvent(&e) != 0)
			{
				working = inputHandler->keyDown(e, game);

				SDL_RenderClear(renderer);
				loadWindowWithBackground();
				displaySnake(game);
				displayGameDetails(game, positions);


				if (rules.isOutOfBounds() || working == false || rules.eatItself())
				{
					std::cout << "GAME OVER" << std::endl;
					working = false;
				}
			}


			if (!rules.continuousMovement())
			{
				SDL_RenderClear(renderer);
				loadWindowWithBackground();
				displaySnake(game);
				displayGameDetails(game, positions);

				if (rules.isOutOfBounds() || rules.eatItself())
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


			int frameTicks = capTimer.getTicks();
			if (frameTicks < SCREEN_TICK_PER_FRAME)
			{
				//Wait remaining time
				SDL_Delay(delay);
			}
		}
	}
	SDL_Quit();
}
#pragma endregion

bool Game::hasTheGameStarted()
{
	return init();
}

Game::~Game()
{
	SDL_RenderPresent(renderer);
}

