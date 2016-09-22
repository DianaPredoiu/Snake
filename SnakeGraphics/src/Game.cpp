#include "Game.h"
#include <Windows.h>
#include "Presets.h"
#include "SQLite.h"
#include <Player.h>

Game::Game()
{
	working = init();
	loadTextures();

	//delay = 500;

	inputHandler = new InputHandler();
	textColor = { 0, 0, 0, 0 };

	scoreTexture.init();
	bonusTexture.init();
	surpriseTexture.init();

	newGameButton = new Button(newGame, 295, 360, 200, 50);
	aboutButton = new Button(about, 295, 430, 200, 50);
	viewScoresButton = new Button(viewScores, 295, 500, 200, 50);
	addScoreButton = new Button(addScore, 500, 240, 50, 50);
	easyGameButton = new Button(easy, 270, 300, 200, 50);
	mediumGameButton = new Button(medium, 270, 400, 200, 50);
	hardGameButton = new Button(hard, 270, 500, 200, 50);
	backToMenuButton = new Button(back, 50, 50, 50, 50);
	

	background = nullptr;

	step = 50;

	scoreTexture.setPath("/sarpe/BuxtonSketch.ttf");
	inputTextTexture.setPath("/sarpe/BuxtonSketch.ttf");
	displayTop3.setPath("/sarpe/BuxtonSketch.ttf");

	scoreTexture.init();
	inputTextTexture.init();
	displayTop3.init();

	scoreText = " ";
	inputText = " ";
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
	if (background == nullptr)
		background = IMG_LoadTexture(renderer, p.c_str());

	while (SDL_RenderCopy(renderer, background, NULL, NULL) == -1)
	{
		background = IMG_LoadTexture(renderer, p.c_str());
	}
}

void Game::loadWindowStartGameBackground()
{
	delete background;
	SDL_RenderClear(renderer);
	// get the path to the img source folder
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/snake-start.png");
	// load img and print on window
	background = IMG_LoadTexture(renderer, p.c_str());

	SDL_RenderCopy(renderer, background, NULL, NULL);
	//delete background;
	background = nullptr;
}

void Game::loadWindowAboutBackground()
{
	delete background;
	SDL_RenderClear(renderer);
	// get the path to the img source folder
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/snake-about.png");
	// load img and print on window
	background = IMG_LoadTexture(renderer, p.c_str());

	SDL_RenderCopy(renderer, background, NULL, NULL);
	//delete background;
	background = nullptr;
}

void Game::loadWindowScoresBackground()
{
	delete background;
	SDL_RenderClear(renderer);
	// get the path to the img source folder
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/snake-scores.png");
	// load img and print on window
	background = IMG_LoadTexture(renderer, p.c_str());

	SDL_RenderCopy(renderer, background, NULL, NULL);
	//delete background;
	background = nullptr;
}

void Game::loadWindowEndGameBackground()
{
	SDL_RenderClear(renderer);
	// get the path to the img source folder
	std::string p = FOO;
	// and attach the img folder to the project source path
	p.append("/sarpe/snake-end2.png");
	// load img and print on window
	background = IMG_LoadTexture(renderer, p.c_str());

	SDL_RenderCopy(renderer, background, NULL, NULL);
	//delete background;
	background = nullptr;
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
	addScoreTexture.loadFromFile("addScore.png", renderer);
	easyGameTexture.loadFromFile("easyGame.png", renderer);
	mediumGameTexture.loadFromFile("mediumGame.png", renderer);
	hardGameTexture.loadFromFile("hardGame.png", renderer);
	backToMenuTexture.loadFromFile("back.png", renderer);
	aboutTexture.loadFromFile("about.png", renderer);
	viewScoresTexture.loadFromFile("scores.png", renderer);
}


#pragma region display items + snake + details
void Game::displayItem(int x, int y, char c)
{
	switch (c)
	{
	case 'F':
		printImage('F', x * step + 10, y * step + 10, 0);
		break;
	case 'B':
		printImage('B', x * step + 10, y * step + 10, 0); \
			break;
	case '?':
		printImage('?', x * step + 10, y * step + 10, 0);
		break;
	}
}

void Game::displaySnake(GameMap &game, int difficulty)
{
	int s = game.getSnake().getCoordinates().size() - 1;
	printImage('T', game.getSnake().getCoordinates().at(s)->getX() * step + 10, game.getSnake().getCoordinates().at(s)->getY() * step + 10, tailDirection(game));

	for (int i = game.getSnake().getCoordinates().size() - 2; i >= 0; i--)
	{
		if (i != 0)
		{

			if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX() + 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step + 10, game.getSnake().getCoordinates().at(i)->getY() *step + 10, -90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX() - 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step + 10, game.getSnake().getCoordinates().at(i)->getY() *step + 10, 90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY() - 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step + 10, game.getSnake().getCoordinates().at(i)->getY() *step + 10, 90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i - 1)->getY() + 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i - 1)->getX())
			{
				printImage('b', game.getSnake().getCoordinates().at(i)->getX() *step + 10, game.getSnake().getCoordinates().at(i)->getY() * step + 10, 90);

			}
		}
		else
		{
			if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX() - 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() * step + 10, game.getSnake().getCoordinates().at(i)->getY() *step + 10, 90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX() + 1
				&& game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() * step + 10, game.getSnake().getCoordinates().at(i)->getY() *step + 10, -90);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY() - 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() *step + 10, game.getSnake().getCoordinates().at(i)->getY() * step + 10, 180);

			}
			else if (game.getSnake().getCoordinates().at(i)->getY() == game.getSnake().getCoordinates().at(i + 1)->getY() + 1
				&& game.getSnake().getCoordinates().at(i)->getX() == game.getSnake().getCoordinates().at(i + 1)->getX())
			{
				printImage('H', game.getSnake().getCoordinates().at(i)->getX() *step + 10, game.getSnake().getCoordinates().at(i)->getY() *step + 10, 0);

			}
		}

	}

	if (game.getBonus().getState())
	{
		displayItem(game.getBonus().getCoordinates().getX(), game.getBonus().getCoordinates().getY(), 'B');
	}
	else if (game.getSurprise().getState())
	{
		displayItem(game.getSurprise().getCoordinates().getX(), game.getSurprise().getCoordinates().getY(), '?');
	}
	else if (game.getFood().getState())
	{
		game.addFood();
		displayItem(game.getFood().getCoordinates().getX(), game.getFood().getCoordinates().getY(), 'F');
	}

}

void Game::displayGameDetails(GameMap &game, std::vector<Position*> pos)
{
	game.initializeGrid(pos);

	//rectangles for score and chrono for bonus and surprise
	scoreTexture.loadFromRenderedText(std::to_string(game.getScore()), textColor, renderer);
	printText(scoreTexture, 155, 770, 0, 60, 40);

	if (game.getBonus().getTime() != 0 && game.getBonus().getState())
	{
		bonusTexture.loadFromRenderedText(std::to_string(game.getBonus().getTime()), textColor, renderer);
		printText(bonusTexture, 390, 770, 0, 60, 40);
	}

	if (game.getSurprise().getTime() != 0 && game.getSurprise().getState())
	{
		surpriseTexture.loadFromRenderedText(std::to_string(game.getSurprise().getTime()), textColor, renderer);
		printText(surpriseTexture, 670, 770, 0, 60, 40);
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


#pragma region Print to screen

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
}

void Game::printText(Texture textureName, int x, int y, int angle, int w, int h)
{
	SDL_Rect rectangle;

	int a, b;
	SDL_QueryTexture(textureName.GetTexture(), NULL, NULL, &a, &b);

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = textureName.w;
	rectangle.h = textureName.h;

	SDL_RenderCopyEx(renderer, textureName.GetTexture(), NULL, &rectangle, angle, NULL, SDL_FLIP_NONE);
}

void Game::printRectTextColored(Texture textureName, int x, int y, int angle, int w, int h)
{
	SDL_Rect rectangle;

	int a, b;
	SDL_QueryTexture(textureName.GetTexture(), NULL, NULL, &a, &b);

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = textureName.w;
	rectangle.h = textureName.h;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rectangle);

	SDL_RenderCopyEx(renderer, textureName.GetTexture(), NULL, &rectangle, angle, NULL, SDL_FLIP_NONE);
}

#pragma endregion


#pragma region Execution

void Game::startGamePage()
{
	//SDL_Event e;
	if (working)
	{
		//here i display all the buttons which must be in the start page

		loadWindowStartGameBackground();
		SDL_RenderCopyEx(renderer, newGameTexture.GetTexture(), NULL, &newGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, aboutTexture.GetTexture(), NULL, &aboutButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, viewScoresTexture.GetTexture(), NULL, &viewScoresButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);

		while (SDL_WaitEvent(&e) != 0)
		{
			//when an event appears i check what button is pressed :  new game, load game or quit game
			if (newGameButton->isPressed(e))
				chooseLevelPage();
			if (aboutButton->isPressed(e))
				aboutPage();
			if (viewScoresButton->isPressed(e))
				scoresPage();
			if (e.type == SDL_QUIT)
				SDL_Quit();
		}

	}

}

void Game::chooseLevelPage()
{
	newGameButton->setCoordinates(295, 360);
	aboutButton->setCoordinates(295, 430);
	viewScoresButton->setCoordinates(295, 500);

	if (working)
	{
		loadWindowStartGameBackground();

		SDL_RenderCopyEx(renderer, backToMenuTexture.GetTexture(), NULL, &backToMenuButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, easyGameTexture.GetTexture(), NULL, &easyGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, mediumGameTexture.GetTexture(), NULL, &mediumGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, hardGameTexture.GetTexture(), NULL, &hardGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);

		while (SDL_WaitEvent(&e) != 0)
		{
			if (easyGameButton->isPressed(e))
				executeGame(300);
			if (mediumGameButton->isPressed(e))
				executeGame(200);
			if (hardGameButton->isPressed(e))
				executeGame(50);
			if (backToMenuButton->isPressed(e))
				startGamePage();
			if (e.type == SDL_QUIT)
				SDL_Quit();
		}
	}
}

void Game::aboutPage()
{
	if (working)
	{
		loadWindowAboutBackground();
		SDL_RenderCopyEx(renderer, backToMenuTexture.GetTexture(), NULL, &backToMenuButton->getBox(), 0, NULL, SDL_FLIP_NONE);

		SDL_RenderPresent(renderer);

		while (SDL_WaitEvent(&e) != 0)
		{
			if (backToMenuButton->isPressed(e))
				startGamePage();
			if (e.type == SDL_QUIT)
				SDL_Quit();
		}
	}
}

void Game::scoresPage()
{
	if (working)
	{
		SQLite sql;

		loadWindowScoresBackground();
		SDL_RenderCopyEx(renderer, backToMenuTexture.GetTexture(), NULL, &backToMenuButton->getBox(), 0, NULL, SDL_FLIP_NONE);

		SDL_RenderPresent(renderer);

		sql.select("easy");
		std::vector<Player> easyPlayers=sql.getPlayers();

		sql.select("medium");
		std::vector<Player> mediumPlayers = sql.getPlayers();

		sql.select("hard");
		std::vector<Player> hardPlayers = sql.getPlayers();

		//print players

		while (SDL_WaitEvent(&e) != 0)
		{
			if (backToMenuButton->isPressed(e))
				startGamePage();
			if (e.type == SDL_QUIT)
				SDL_Quit();
		}
	}
}

void Game::endGamePage(int score, int difficulty)
{
	SQLite sql;
	scoreText = " ";
	inputText = "write here";
	bool firstchar = true;
	scoreText.append(std::to_string(score));

	newGameButton->setCoordinates(290, 700);
	addScoreButton->setCoordinates(290, 325);

	if (!working)
	{
		loadWindowEndGameBackground();
		SDL_RenderCopyEx(renderer, newGameTexture.GetTexture(), NULL, &newGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, addScoreTexture.GetTexture(), NULL, &addScoreButton->getBox(), 0, NULL, SDL_FLIP_NONE);

		displayScoreTexture.loadFromRenderedText(scoreText, textColor, renderer);
		printText(scoreTexture, 290, 215, 0, 50, 50);

		inputTextTexture.loadFromRenderedText(inputText, textColor, renderer);
		printText(inputTextTexture, 100, 330, 0, 200, 40);

		SDL_RenderPresent(renderer);

		SDL_StartTextInput();
		while (SDL_WaitEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN && inputText.size() < 15)
			{
				if (firstchar == true)
				{
					inputText = " ";
					firstchar = false;
				}
				//Handle backspace
				if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
				{
					inputText.pop_back();
				}
				//handle copy
				else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(inputText.c_str());
				}
				//handle paste
				else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					inputText = SDL_GetClipboardText();
				}
				//If the key is a blank space
				if (e.key.keysym.sym == (Uint16)' ')
				{
					inputText += (char)e.key.keysym.sym;
				}
				//If the key is a number
				else if ((e.key.keysym.sym >= (Uint16)'0') && (e.key.keysym.sym <= (Uint16)'9'))
				{
					inputText += (char)e.key.keysym.sym;
				}
				//If the key is a uppercase letter
				else if ((e.key.keysym.sym >= (Uint16)'A') && (e.key.keysym.sym <= (Uint16)'Z'))
				{
					inputText += (char)e.key.keysym.sym;
				}
				//If the key is a lowercase letter
				else if ((e.key.keysym.sym >= (Uint16)'a') && (e.key.keysym.sym <= (Uint16)'z'))
				{
					inputText += (char)e.key.keysym.sym;
				}


				loadWindowEndGameBackground();
				SDL_RenderCopyEx(renderer, newGameTexture.GetTexture(), NULL, &newGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
				SDL_RenderCopyEx(renderer, addScoreTexture.GetTexture(), NULL, &addScoreButton->getBox(), 0, NULL, SDL_FLIP_NONE);

				displayScoreTexture.loadFromRenderedText(scoreText, textColor, renderer);
				printText(scoreTexture, 290, 215, 0, 50, 50);

				inputTextTexture.loadFromRenderedText(inputText, textColor, renderer);
				printText(inputTextTexture, 100, 330, 0, 200, 40);

				SDL_RenderPresent(renderer);

			}

			if (newGameButton->isPressed(e))
			{
				working = true;
				chooseLevelPage();
			}
			if (addScoreButton->isPressed(e))
			{
				//insert score in database
				std::string level;
				if (difficulty == HARDLEVEL)
					level = "hard";
				else
				if (difficulty == MEDIUMLEVEL)
					level = "medium";
				else
					level = "easy";

				sql.insert(Player(inputText, score,level));

				//select top 5 with the same level
				sql.select(level);
				sql.getPlayers();
				//print players
			}

			if (e.type == SDL_QUIT)
				SDL_Quit();
		}

		SDL_StopTextInput();
	}
}

void Game::executeGame(int difficulty)
{
	GameMap game(15, 15);
	Rules rules(&game);
	InputHandler *inputHandler;

	std::vector<Position*> positions = game.initializeGrid(game.getSnake().getCoordinates());

	game.setScore(0);

	delay = difficulty;

	if (!working)
	{
		std::cout << "Failed to initialize!\n" << std::endl;
	}
	else
	{
		loadWindowGameBackground();
		displaySnake(game, difficulty);
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
				if (e.type == SDL_QUIT)
					SDL_Quit();
				working = inputHandler->keyDown(e, game);

				loadWindowGameBackground();
				displaySnake(game, difficulty);
				displayGameDetails(game, positions);
				SDL_RenderPresent(renderer);

				if (rules.isOutOfBounds() || working == false || rules.eatItself())
				{
					std::cout << "GAME OVER" << std::endl;
					working = false;
					endGamePage(game.getScore(),difficulty);
				}
			}


			if (!rules.continuousMovement())
			{
				loadWindowGameBackground();
				displaySnake(game, difficulty);
				displayGameDetails(game, positions);
				SDL_RenderPresent(renderer);

				if (rules.isOutOfBounds() || rules.eatItself())
				{
					std::cout << "GAME OVER!" << std::endl;
					working = false;
					endGamePage(game.getScore(),difficulty);
				}
			}
			else
			{
				std::cout << "GAME OVER!" << std::endl;
				working = false;
				endGamePage(game.getScore(),difficulty);
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



Game::~Game()
{
	SDL_RenderPresent(renderer);
	delete newGameButton;
	delete aboutButton;
	delete addScoreButton;
	delete easyGameButton;
	delete mediumGameButton;
	delete hardGameButton;
	delete aboutButton;

	delete inputHandler;

	delete screenSurface;
	delete window;
	delete background;
	delete renderer;
}

