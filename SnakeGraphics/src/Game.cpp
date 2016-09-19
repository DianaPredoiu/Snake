#include "Game.h"
#include <Windows.h>
#include "Presets.h"

Game::Game()
{
	working = init();
	loadTextures();

	delay = 150;

	inputHandler = new InputHandler();
	textColor = { 0, 0, 0, 50 };

	scoreTexture.init();
	bonusTexture.init();
	surpriseTexture.init();

	newGameButton = new Button(newGame, 295, 360, 200, 50);
	loadGameButton = new Button(loadGame, 295, 430, 200, 50);
	replayGameButton = new Button(replayGame, 295, 360, 200, 50);
	quitGameButton = new Button(quitGame, 295, 430, 200, 50);

	step = 50;

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
		window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void Game::loadWindowGameBackground()
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

void Game::loadWindowStartGameBackground()
{
	SDL_RenderClear(renderer);
	// get the path to the img source folder
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/grass-original.png");
	// load img and print on window
	background = IMG_LoadTexture(renderer, p.c_str());

	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Game::loadWindowEndGameBackground()
{
	SDL_RenderClear(renderer);
	// get the path to the img source folder
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/grass-end.png");
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

	newGameTexture.loadFromFile("newGame.png", renderer);
	loadGameTexture.loadFromFile("loadGame.png", renderer);
	replayGameTexture.loadFromFile("replayGame.png", renderer);
	quitGameTexture.loadFromFile("quitGame.png", renderer);
	//addScoreTexture.loadFromFile("addScore.png", renderer);
}


#pragma region display items + snake + details
void Game::displayFood(int x, int y)
{
	printImage('F', x * step + 20, y * step + 20, 0);
}

void Game::displayBonus(int x, int y)
{
	printImage('B', x * step + 20, y * step + 20, 0);
	delay = 50;

}

void Game::displaySurprise(int x, int y)
{
	printImage('?', x * step + 20, y * step + 20, 0);
	delay = 50;
}

void Game::displaySnake(GameMap &game)
{
	int s = game.getSnake().getCoordinates().size() - 1;
	printImage('T', game.getSnake().getCoordinates().at(s)->getX() * step + 20, game.getSnake().getCoordinates().at(s)->getY() * step + 20, tailDirection(game));

	for (int i = game.getSnake().getCoordinates().size() - 2; i >= 0; i--)
	{
		if (i != 0)
		{

			if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX() + 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step + 20, game.getSnake().getCoordinates().at(i)->getY() *step + 20, -90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX() - 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step + 20, game.getSnake().getCoordinates().at(i)->getY() *step + 20, 90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY() - 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step + 20, game.getSnake().getCoordinates().at(i)->getY() *step + 20, 90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY() + 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step + 20, game.getSnake().getCoordinates().at(i)->getY() * step + 20, 90);

			}
		}
		else
		{
			if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX() - 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() * step + 20, game.getSnake().getCoordinates().at(i)->getY() *step + 20, 90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX() + 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() * step + 20, game.getSnake().getCoordinates().at(i)->getY() *step + 20, -90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY() - 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() *step + 20, game.getSnake().getCoordinates().at(i)->getY() * step + 20, 180);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY() + 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() *step + 20, game.getSnake().getCoordinates().at(i)->getY() *step + 20, 0);

			}
		}

	}

	if (game.getBonus().getState())
	{
		displayBonus(game.getBonus().getCoordinates().getX(), game.getBonus().getCoordinates().getY());
	}
	else if (game.getSurprise().getState())
	{
		displaySurprise(game.getSurprise().getCoordinates().getX(), game.getSurprise().getCoordinates().getY());
	}
	else if (game.getFood().getState())
	{
		game.addFood();
		displayFood(game.getFood().getCoordinates().getX(), game.getFood().getCoordinates().getY());
		delay = 150;
	}

}

void Game::displayGameDetails(GameMap &game, std::vector<Position*> pos)
{
	game.initializeGrid(pos);

	//rectangles for score and chrono for bonus and surprise
	scoreTexture.loadFromRenderedText(std::to_string(game.getScore()), textColor, renderer);
	printScores(scoreTexture, 110, 795, 0);

	if (game.getBonus().getTime() != 0 && game.getBonus().getState())
	{
		bonusTexture.loadFromRenderedText(std::to_string(game.getBonus().getTime()), textColor, renderer);
		printScores(bonusTexture, 400, 795, 0);
	}

	if (game.getSurprise().getTime() != 0 && game.getSurprise().getState())
	{
		surpriseTexture.loadFromRenderedText(std::to_string(game.getSurprise().getTime()), textColor, renderer);
		printScores(surpriseTexture, 680, 795, 0);
	}

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
	rectangle.w = 50;
	rectangle.h = 50;

	SDL_RenderCopyEx(renderer, textures[textureName], NULL, &rectangle, angle, NULL, SDL_FLIP_NONE);
	//SDL_RenderPresent(renderer);
}

void Game::printScores(Texture textureName, int x, int y, int angle)
{
	SDL_Rect rectangle;

	int a, b;
	SDL_QueryTexture(textureName.GetTexture(), NULL, NULL, &a, &b);

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = 60;
	rectangle.h = 40;

	SDL_RenderCopyEx(renderer, textureName.GetTexture(), NULL, &rectangle, angle, NULL, SDL_FLIP_NONE);
	//SDL_RenderPresent(renderer);
}


#pragma region Execution

void Game::startGamePage()
{
	
	SDL_Event e;
	if (working)
	{
		//here i display all the buttons which must be in the start page

		loadWindowStartGameBackground();
		SDL_RenderCopyEx(renderer, newGameTexture.GetTexture(), NULL, &newGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, loadGameTexture.GetTexture(), NULL, &loadGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);

		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				//when an event appears i check what button is pressed :  new game, load game or quit game
				if (newGameButton->isPressed(e))
					executeGame();
				if (loadGameButton->isPressed(e))
					loadWindowEndGameBackground();
				if (e.type == SDL_QUIT)
					quit = true;
			}
		}
	}
		
}

void Game::endGamePage()
{
	SDL_Event e;
	if (working == false)
	{
		loadWindowEndGameBackground();
		SDL_RenderCopyEx(renderer, replayGameTexture.GetTexture(), NULL, &replayGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, quitGameTexture.GetTexture(), NULL, &quitGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		//SDL_RenderCopyEx(renderer, addScoreTexture.GetTexture(), NULL, &addScoreButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);

		bool quit = false;
		
		while (!quit)
		{
			while ( SDL_PollEvent(&e) != 0)
			{
				////////asta nu prea vrea sa mearga/////
				if (replayGameButton->isPressed(e))
					executeGame();
				if (quitGameButton->isPressed(e))
					quit = true;
				//if (addScoreButton->isPressed(e))
					//adauga in baza de date
				if (e.type == SDL_QUIT)
					quit = true;
			}
		}
	}	
}

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
		loadWindowGameBackground();
		displaySnake(game);
		displayGameDetails(game, positions);
		SDL_RenderPresent(renderer);
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
		//int delta_time = currentTime - lastUpdateTime * 10;

		SDL_Event e;
		while (working)
		{		
			capTimer.start();
			while (SDL_PollEvent(&e) != 0 && working)
			{
				working = inputHandler->keyDown(e, game);

				loadWindowGameBackground();
				displaySnake(game);
				displayGameDetails(game, positions);
				SDL_RenderPresent(renderer);

				if (rules.isOutOfBounds() || working == false || rules.eatItself())
				{
					std::cout << "GAME OVER" << std::endl;
					working = false;
					endGamePage();
				}
			}


			if (!rules.continuousMovement())
			{
				loadWindowGameBackground();
				displaySnake(game);
				displayGameDetails(game, positions);
				SDL_RenderPresent(renderer);

				if (rules.isOutOfBounds() || rules.eatItself())
				{
					std::cout << "GAME OVER!" << std::endl;
					working = false;
					endGamePage();
				}
			}
			else
			{
				std::cout << "GAME OVER!" << std::endl;
				working = false;
				endGamePage();
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
	delete newGameButton;
	delete loadGameButton;
	delete replayGameButton;
	delete quitGameButton;
	//delete addScoreButton;

	delete inputHandler;

	delete screenSurface;
	delete window;
	delete background;
	delete renderer;
}

