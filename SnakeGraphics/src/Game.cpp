#include "Game.h"
#include <Windows.h>
#include "Presets.h"
#include "SQLite.h"
#include <Player.h>
#include <thread>
#include "SDL_mixer.h"

Game::Game()
{
	working = init();
	loadItemTextures();
	loadButtonTextures();
	loadBackgroundTextures();

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
	playSoundButton = new Button(sound, 50, 750, 50, 50);

	scoreTexture.setPath("/sarpe/BuxtonSketch.ttf");
	inputTextTexture.setPath("/sarpe/BuxtonSketch.ttf");
	displayTop5Easy.setPath("/sarpe/BuxtonSketch.ttf");
	displayTop5Medium.setPath("/sarpe/BuxtonSketch.ttf");
	displayTop5Hard.setPath("/sarpe/BuxtonSketch.ttf");

	scoreTexture.init();
	inputTextTexture.init();
	displayTop5Easy.init();
	displayTop5Medium.init();
	displayTop5Hard.init();

	scoreText = " ";
	inputText = " ";
	step = 50;

	loadSounds();
	currentChannel = 0;
	isSoundMuted = false;
}

bool Game::init()
{
	screenSurface = NULL;
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
			//Initialize SDL_mixer
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				success = false;
			}
		}
	}

	return success;
}

void Game::loadSounds()
{
	std::string p = FOO;
	p.append("/sound/food.wav");
	foodSound = Mix_LoadWAV(p.c_str());

	p = FOO;
	p.append("/sound/start.wav");
	mainSound = Mix_LoadWAV(p.c_str());

	p = FOO;
	p.append("/sound/over_.wav");
	gameOverSound = Mix_LoadWAV(p.c_str());

	p = FOO;
	p.append("/sound/bonus.wav");
	bonusSound = Mix_LoadWAV(p.c_str());

	p = FOO;
	p.append("/sound/surprise.wav");
	surpriseSound = Mix_LoadWAV(p.c_str());
}

#pragma region loading textures
void Game::loadWindowGameBackground()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgrounds["playGame"], NULL, NULL);
}

void Game::loadWindowStartGameBackground()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgrounds["startGame"], NULL, NULL);
}

void Game::loadWindowAboutBackground()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgrounds["about"], NULL, NULL);
}

void Game::loadWindowScoresBackground()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgrounds["score"], NULL, NULL);
}

void Game::loadWindowEndGameBackground()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgrounds["endGame"], NULL, NULL);

}

void Game::loadItemTextures()
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

void Game::loadButtonTextures()
{
	newGameTexture.loadFromFile("newGame.png", renderer);
	buttons["newGame"] = newGameTexture.GetTexture();

	addScoreTexture.loadFromFile("addScore.png", renderer);
	buttons["addScore"] = addScoreTexture.GetTexture();

	easyGameTexture.loadFromFile("easyGame.png", renderer);
	buttons["easy"] = easyGameTexture.GetTexture();

	mediumGameTexture.loadFromFile("mediumGame.png", renderer);
	buttons["medium"] = mediumGameTexture.GetTexture();

	hardGameTexture.loadFromFile("hardGame.png", renderer);
	buttons["hard"] = hardGameTexture.GetTexture();

	backToMenuTexture.loadFromFile("back.png", renderer);
	buttons["back"] = backToMenuTexture.GetTexture();

	aboutTexture.loadFromFile("about.png", renderer);
	buttons["about"] = aboutTexture.GetTexture();

	viewScoresTexture.loadFromFile("scores.png", renderer);
	buttons["scores"] = viewScoresTexture.GetTexture();

	playSoundTexture.loadFromFile("sound.png", renderer);
	buttons["sound"] =playSoundTexture.GetTexture();
}

void Game::loadBackgroundTextures()
{
	std::string p;

	p = FOO;
	p.append("/sarpe/grass.png");
	backgroundPlayGame = IMG_LoadTexture(renderer, p.c_str());
	backgrounds["playGame"] = backgroundPlayGame;

	p = FOO;
	p.append("/sarpe/snake-start.png");
	backgroundStartGame = IMG_LoadTexture(renderer, p.c_str());
	backgrounds["startGame"] = backgroundStartGame;

	p = FOO;
	p.append("/sarpe/snake-start.png");
	backgroundChooseLevel = IMG_LoadTexture(renderer, p.c_str());
	backgrounds["chooseLevel"] = backgroundChooseLevel;

	p = FOO;
	p.append("/sarpe/snake-end2.png");
	backgroundEndGame = IMG_LoadTexture(renderer, p.c_str());
	backgrounds["endGame"] = backgroundEndGame;

	p = FOO;
	p.append("/sarpe/snake-scores2.png");
	backgroundScore = IMG_LoadTexture(renderer, p.c_str());
	backgrounds["score"] = backgroundScore;

	p = FOO;
	p.append("/sarpe/snake-about.png");
	backgroundAbout = IMG_LoadTexture(renderer, p.c_str());
	backgrounds["about"] = backgroundAbout;
}
#pragma endregion


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

		if (game.getBonus().getCoordinates().getX()* step + 10 == game.getSnake().getCoordinates().at(0)->getX()* step + 10
			&& game.getBonus().getCoordinates().getY()* step + 10 == game.getSnake().getCoordinates().at(0)->getY() * step + 10)
		{
			currentChannel = Mix_PlayChannel(-1, bonusSound, 0);
		}
	}
	else if (game.getSurprise().getState())
	{
		displayItem(game.getSurprise().getCoordinates().getX(), game.getSurprise().getCoordinates().getY(), '?');

		if (game.getSurprise().getCoordinates().getX()* step + 10 == game.getSnake().getCoordinates().at(0)->getX()* step + 10
			&& game.getSurprise().getCoordinates().getY()* step + 10 == game.getSnake().getCoordinates().at(0)->getY() * step + 10)
		{
			currentChannel = Mix_PlayChannel(-1, surpriseSound, 0);
		}
	}
	else if (game.getFood().getState())
	{
		game.addFood();
		displayItem(game.getFood().getCoordinates().getX(), game.getFood().getCoordinates().getY(), 'F');

		if (game.getFood().getCoordinates().getX()* step + 10 == game.getSnake().getCoordinates().at(0)->getX()* step + 10
			&& game.getFood().getCoordinates().getY()* step + 10 == game.getSnake().getCoordinates().at(0)->getY() * step + 10)
		{
			currentChannel = Mix_PlayChannel(-1, foodSound, 0);
		}
	}

}

void Game::displayGameDetails(GameMap &game, std::vector<Position*> pos)
{
	game.initializeGrid(pos);

	//rectangles for score and chrono for bonus and surprise
	scoreTexture.loadFromRenderedText(std::to_string(game.getScore()), textColor, renderer);
	printText(scoreTexture, 155, 770);

	if (game.getBonus().getTime() != 0 && game.getBonus().getState())
	{
		bonusTexture.loadFromRenderedText(std::to_string(game.getBonus().getTime()), textColor, renderer);
		printText(bonusTexture, 390, 770);
	}

	if (game.getSurprise().getTime() != 0 && game.getSurprise().getState())
	{
		surpriseTexture.loadFromRenderedText(std::to_string(game.getSurprise().getTime()), textColor, renderer);
		printText(surpriseTexture, 670, 770);
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

void Game::printText(Texture textureName, int x, int y)
{
	SDL_Rect rectangle;

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = textureName.w;
	rectangle.h = textureName.h;

	SDL_RenderCopyEx(renderer, textureName.GetTexture(), NULL, &rectangle, 0, NULL, SDL_FLIP_NONE);
}

void Game::printTextScores(Texture textureName, int x, int y, int angle, int w, int h)
{
	SDL_Rect rectangle;

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;

	SDL_RenderCopyEx(renderer, textureName.GetTexture(), NULL, &rectangle, angle, NULL, SDL_FLIP_NONE);
}

#pragma endregion


#pragma region Execution

void Game::startGamePage()
{
	if (working)
	{
		//here i display all the buttons which must be in the start page

		loadWindowStartGameBackground();
		SDL_RenderCopyEx(renderer, buttons["newGame"], NULL, &newGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["about"], NULL, &aboutButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["scores"], NULL, &viewScoresButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["sound"], NULL, &playSoundButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);

		if (isSoundMuted)
		{
			Mix_HaltChannel(currentChannel);
		}
		else
		{
			Mix_HaltChannel(currentChannel);
			currentChannel = Mix_PlayChannel(-1, mainSound, -1);
		}

		while (SDL_WaitEvent(&e) != 0)
		{
			//when an event appears i check what button is pressed :  new game, load game or quit game

			if (newGameButton->isPressed(e))
			{
				chooseLevelPage();
			}
			if (aboutButton->isPressed(e))
			{
				aboutPage();
			}
			if (viewScoresButton->isPressed(e))
			{
				scoresPage();
			}
			if (playSoundButton->isPressed(e))
			{
				if (isSoundMuted)
				{
					isSoundMuted = false;
					Mix_HaltChannel(currentChannel);
					currentChannel = Mix_PlayChannel(-1, mainSound, -1);
				}
				else
				{
					isSoundMuted = true;
					Mix_HaltChannel(currentChannel);
					
				}

			}
			if (e.type == SDL_QUIT)
				SDL_Quit();
		}
	}
}

void Game::chooseLevelPage()
{
	if (isSoundMuted)
	{
		Mix_HaltChannel(currentChannel);
	}
	else
	{
		Mix_HaltChannel(currentChannel);
		currentChannel = Mix_PlayChannel(-1, mainSound, -1);
	}

	newGameButton->setCoordinates(295, 360);
	aboutButton->setCoordinates(295, 430);
	viewScoresButton->setCoordinates(295, 500);

	if (working)
	{
		loadWindowStartGameBackground();

		SDL_RenderCopyEx(renderer, buttons["back"], NULL, &backToMenuButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["easy"], NULL, &easyGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["medium"], NULL, &mediumGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["hard"], NULL, &hardGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["sound"], NULL, &playSoundButton->getBox(), 0, NULL, SDL_FLIP_NONE);
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
			if (playSoundButton->isPressed(e))
			{
				if (isSoundMuted)
				{
					isSoundMuted = false;
					Mix_HaltChannel(currentChannel);
					currentChannel = Mix_PlayChannel(-1, mainSound, -1);
				}
				else
				{
					isSoundMuted = true;
					Mix_HaltChannel(currentChannel);
					
				}

			}
			if (e.type == SDL_QUIT)
				SDL_Quit();
		}
	}
}

void Game::aboutPage()
{
	if (isSoundMuted)
	{
		Mix_HaltChannel(currentChannel);
	}
	else
	{
		Mix_HaltChannel(currentChannel);
		currentChannel = Mix_PlayChannel(-1, mainSound, -1);
	}

	if (working)
	{
		loadWindowAboutBackground();
		SDL_RenderCopyEx(renderer, buttons["back"], NULL, &backToMenuButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["sound"], NULL, &playSoundButton->getBox(), 0, NULL, SDL_FLIP_NONE);

		SDL_RenderPresent(renderer);

		while (SDL_WaitEvent(&e) != 0)
		{
			if (backToMenuButton->isPressed(e))
				startGamePage();
			if (playSoundButton->isPressed(e))
			{
				if (isSoundMuted)
				{
					isSoundMuted = false;
					Mix_HaltChannel(currentChannel);
					currentChannel = Mix_PlayChannel(-1, mainSound, -1);
				}
				else
				{
					isSoundMuted = true;
					Mix_HaltChannel(currentChannel);
					
				}

			}
			if (e.type == SDL_QUIT)
				SDL_Quit();
		}
	}
}

void Game::scoresPage()
{
	if (isSoundMuted)
	{
		Mix_HaltChannel(currentChannel);
	}
	else
	{
		Mix_HaltChannel(currentChannel);
		currentChannel = Mix_PlayChannel(-1, mainSound, -1);
	}

	easyLevelPlayers = " ";
	mediumLevelPlayers = " ";
	hardLevelPlayers = " ";
	if (working)
	{
		populateEasyLevelPlayers();
		populateMediumLevelPlayers();
		populateHardLevelPlayers();

		loadWindowScoresBackground();
		SDL_RenderCopyEx(renderer, buttons["back"], NULL, &backToMenuButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["sound"], NULL, &playSoundButton->getBox(), 0, NULL, SDL_FLIP_NONE);

		displayTop5Easy.loadFromRenderedTextWrapped(easyLevelPlayers, textColor, renderer);
		printTextScores(displayTop5Easy, 20, 170, 0, 170, 150);

		displayTop5Medium.loadFromRenderedTextWrapped(mediumLevelPlayers, textColor, renderer);
		printTextScores(displayTop5Medium, 20, 360, 0, 170, 150);

		displayTop5Hard.loadFromRenderedTextWrapped(hardLevelPlayers, textColor, renderer);
		printTextScores(displayTop5Hard, 20, 550, 0, 170, 150);

		SDL_RenderPresent(renderer);

		while (SDL_WaitEvent(&e) != 0)
		{
			if (backToMenuButton->isPressed(e))
				startGamePage();
			if (playSoundButton->isPressed(e))
			{
				if (isSoundMuted)
				{
					isSoundMuted = false;
					Mix_HaltChannel(currentChannel);
					currentChannel = Mix_PlayChannel(-1, mainSound, -1);
				}
				else
				{
					isSoundMuted = true;
					Mix_HaltChannel(currentChannel);
					
				}

			}
			if (e.type == SDL_QUIT)
				SDL_Quit();
		}
	}
}

void Game::endGamePage(int score, int difficulty)
{
	if (isSoundMuted)
	{
		Mix_HaltChannel(currentChannel);
	}
	else
	{
		Mix_HaltChannel(currentChannel);
		currentChannel = Mix_PlayChannel(-1, mainSound, -1);
	}

	SQLite sql;
	scoreText = " ";
	inputText = "player's name";
	level = " ";
	bool firstchar = true;
	scoreText.append(std::to_string(score));

	newGameButton->setCoordinates(290, 700);
	addScoreButton->setCoordinates(290, 325);

	if (!working)
	{
		loadWindowEndGameBackground();
		SDL_RenderCopyEx(renderer, buttons["sound"], NULL, &playSoundButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["newGame"], NULL, &newGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, buttons["addScore"], NULL, &addScoreButton->getBox(), 0, NULL, SDL_FLIP_NONE);
		

		displayScoreTexture.loadFromRenderedText(scoreText, textColor, renderer);
		printText(scoreTexture, 290, 215);

		inputTextTexture.loadFromRenderedText(inputText, textColor, renderer);
		printText(inputTextTexture, 100, 330);

		displayScoreTable(difficulty);

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
				if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.empty() == false)
				{
					inputText.pop_back();
					if (inputText.empty() == true)
						inputText += " ";
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
				SDL_RenderCopyEx(renderer, buttons["newGame"], NULL, &newGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
				SDL_RenderCopyEx(renderer, buttons["addScore"], NULL, &addScoreButton->getBox(), 0, NULL, SDL_FLIP_NONE);
				SDL_RenderCopyEx(renderer, buttons["sound"], NULL, &playSoundButton->getBox(), 0, NULL, SDL_FLIP_NONE);


				displayScoreTexture.loadFromRenderedText(scoreText, textColor, renderer);
				printText(scoreTexture, 290, 215);

				inputTextTexture.loadFromRenderedText(inputText, textColor, renderer);
				printText(inputTextTexture, 100, 330);

				displayScoreTable(difficulty);
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

				if (inputText == " " || inputText == "Player added!" || inputText == "Enter a name!" || inputText == "player's name")
				{
					SDL_RenderClear(renderer);
					loadWindowEndGameBackground();
					SDL_RenderCopyEx(renderer, buttons["newGame"], NULL, &newGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
					SDL_RenderCopyEx(renderer, buttons["addScore"], NULL, &addScoreButton->getBox(), 0, NULL, SDL_FLIP_NONE);
					SDL_RenderCopyEx(renderer, buttons["sound"], NULL, &playSoundButton->getBox(), 0, NULL, SDL_FLIP_NONE);

					inputText = "Enter a name!";

					displayScoreTexture.loadFromRenderedText(scoreText, textColor, renderer);
					printText(scoreTexture, 290, 215);

					inputTextTexture.loadFromRenderedText(inputText, textColor, renderer);
					printText(inputTextTexture, 100, 330);

					displayScoreTable(difficulty);
					SDL_RenderPresent(renderer);
				}
				else
				{
					sql.insert(Player(inputText, score, level));

					SDL_RenderClear(renderer);
					loadWindowEndGameBackground();
					SDL_RenderCopyEx(renderer, buttons["newGame"], NULL, &newGameButton->getBox(), 0, NULL, SDL_FLIP_NONE);
					SDL_RenderCopyEx(renderer, buttons["addScore"], NULL, &addScoreButton->getBox(), 0, NULL, SDL_FLIP_NONE);
					SDL_RenderCopyEx(renderer, buttons["sound"], NULL, &playSoundButton->getBox(), 0, NULL, SDL_FLIP_NONE);

					inputText = "Player added!";

					displayScoreTexture.loadFromRenderedText(scoreText, textColor, renderer);
					printText(scoreTexture, 290, 215);

					inputTextTexture.loadFromRenderedText(inputText, textColor, renderer);
					printText(inputTextTexture, 100, 330);

					displayScoreTable(difficulty);
					SDL_RenderPresent(renderer);
				}


			}
			if (playSoundButton->isPressed(e))
			{
				if (isSoundMuted)
				{
					isSoundMuted = false;
					Mix_HaltChannel(currentChannel);
					currentChannel = Mix_PlayChannel(-1, mainSound, -1);
				}
				else
				{
					isSoundMuted = true;
					Mix_HaltChannel(currentChannel);
					
				}

			}
			if (e.type == SDL_QUIT)
				SDL_Quit();
		}

		SDL_StopTextInput();
	}
}

void Game::displayScoreTable(int difficulty)
{
	switch (difficulty)
	{
	case EASYLEVEL:
		level = "Level : EASY";
		displayLevel.loadFromRenderedText(level, textColor, renderer);
		printText(displayLevel, 75, 450);

		populateEasyLevelPlayers();
		displayTop5Easy.loadFromRenderedTextWrapped(easyLevelPlayers, textColor, renderer);
		printTextScores(displayTop5Easy, 25, 485, 0, 200, 200);
		break;
	case MEDIUMLEVEL:
		level = "Level : MEDIUM";
		displayLevel.loadFromRenderedText(level, textColor, renderer);
		printText(displayLevel, 75, 450);

		populateMediumLevelPlayers();
		displayTop5Medium.loadFromRenderedTextWrapped(mediumLevelPlayers, textColor, renderer);
		printTextScores(displayTop5Medium, 25, 485, 0, 200, 200);
		break;
	case HARDLEVEL:
		level = "Level : HARD";
		displayLevel.loadFromRenderedText(level, textColor, renderer);
		printText(displayLevel, 75, 450);

		populateHardLevelPlayers();
		displayTop5Hard.loadFromRenderedTextWrapped(hardLevelPlayers, textColor, renderer);
		printTextScores(displayTop5Hard, 25, 485, 0, 200, 200);
		break;
	}
}

void Game::executeGame(int difficulty)
{
	Mix_HaltChannel(currentChannel);
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
				if (difficulty == EASYLEVEL)
					Sleep(150);
				else if (difficulty == MEDIUMLEVEL)
					Sleep(100);
				else if (difficulty == HARDLEVEL)
					Sleep(50);
				if (rules.isOutOfBounds() || working == false || rules.eatItself())
				{
					std::cout << "GAME OVER" << std::endl;
					working = false;

					Mix_HaltChannel(currentChannel);
					currentChannel = Mix_PlayChannel(-1, gameOverSound, 0);
					SDL_Delay(500);

					endGamePage(game.getScore(), difficulty);
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

					Mix_HaltChannel(currentChannel);
					currentChannel = Mix_PlayChannel(-1, gameOverSound, 0);
					SDL_Delay(500);

					endGamePage(game.getScore(), difficulty);
				}
			}
			else
			{
				std::cout << "GAME OVER!" << std::endl;
				working = false;

				Mix_HaltChannel(currentChannel);
				currentChannel = Mix_PlayChannel(-1, gameOverSound, 0);
				SDL_Delay(500);

				endGamePage(game.getScore(), difficulty);
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

#pragma  region populate levels

void Game::populateEasyLevelPlayers()
{
	SQLite sql;
	easyLevelPlayers = " ";
	sql.select("easy");
	std::vector<Player> easyPlayers = sql.getPlayers();
	for (int i = 0; i < easyPlayers.size(); ++i)
	{
		easyLevelPlayers += easyPlayers.at(i).getPlayerName();
		easyLevelPlayers += " - ";
		easyLevelPlayers += std::to_string(easyPlayers.at(i).getScore());
		easyLevelPlayers += "\n";
		easyLevelPlayers += " ";
	}
}

void Game::populateMediumLevelPlayers()
{
	SQLite sql;
	mediumLevelPlayers = " ";
	sql.select("medium");
	std::vector<Player> mediumPlayers = sql.getPlayers();
	for (int i = 0; i < mediumPlayers.size(); ++i)
	{
		mediumLevelPlayers += mediumPlayers.at(i).getPlayerName();
		mediumLevelPlayers += " - ";
		mediumLevelPlayers += std::to_string(mediumPlayers.at(i).getScore());
		mediumLevelPlayers += "\n";
		mediumLevelPlayers += " ";
	}
}

void Game::populateHardLevelPlayers()
{
	SQLite sql;
	hardLevelPlayers = " ";
	sql.select("hard");
	std::vector<Player> hardPlayers = sql.getPlayers();
	for (int i = 0; i < hardPlayers.size(); ++i)
	{
		hardLevelPlayers += hardPlayers.at(i).getPlayerName();
		hardLevelPlayers += " - ";
		hardLevelPlayers += std::to_string(hardPlayers.at(i).getScore());
		hardLevelPlayers += "\n";
		hardLevelPlayers += " ";
	}
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
	delete renderer;

	delete backgroundStartGame;
	delete backgroundChooseLevel;
	delete backgroundEndGame;
	delete backgroundScore;
	delete backgroundAbout;
	delete backgroundPlayGame;

	buttons.clear();
	backgrounds.clear();
	textures.clear();

	Mix_FreeChunk(foodSound);
	foodSound = NULL;

	Mix_FreeChunk(bonusSound);
	bonusSound = NULL;

	Mix_FreeChunk(surpriseSound);
	surpriseSound = NULL;

	Mix_FreeChunk(mainSound);
	mainSound = NULL;

	Mix_FreeChunk(gameOverSound);
	gameOverSound = NULL;
}

