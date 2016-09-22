#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <GameMap.h>
#include <Texture.h>
#include <GameMap.h>
#include <Rules.h>
#include <InputHandler.h>
#include <SymbolTranslation.h>
#include <map>
#include <Timer.h>
#include "Button.h"

class Game{

private:

	bool working;
	int score;
	int step;
	int delay;

	std::string scoreText;
	std::string inputText;
	SDL_Event e;

	SDL_Surface* screenSurface;

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* backgroundStartGame;
	SDL_Texture* backgroundChooseLevel;
	SDL_Texture* backgroundEndGame;
	SDL_Texture* backgroundScore;
	SDL_Texture* backgroundAbout;
	SDL_Texture* backgroundPlayGame;

	Texture displayScoreTexture;
	Texture inputTextTexture;
	Texture displayTop5Easy;
	Texture displayTop5Medium;
	Texture displayTop5Hard;

	Texture scoreTexture;
	Texture bonusTexture;
	Texture surpriseTexture;

	Texture newGameTexture;
	Texture addScoreTexture;
	Texture aboutTexture;
	Texture easyGameTexture;
	Texture mediumGameTexture;
	Texture hardGameTexture;
	Texture backToMenuTexture;
	Texture viewScoresTexture;


	std::map<char, SDL_Texture*> textures;
	std::map<std::string, SDL_Texture*> buttons;
	std::map<std::string, SDL_Texture*> backgrounds;

	InputHandler* inputHandler;

	SDL_Color textColor;
	SDL_Color bgColor;

	Button* newGameButton;
	Button* aboutButton;
	Button* addScoreButton;
	Button* easyGameButton;
	Button* mediumGameButton;
	Button* hardGameButton;
	Button* backToMenuButton;
	Button* viewScoresButton;

	std::string easyLevelPlayers;
	std::string mediumLevelPlayers;
	std::string hardLevelPlayers;


public:
	Game();

	bool init();
	void loadItemTextures();
	void loadButtonTextures();
	void loadBackgroundTextures();

	void loadWindowGameBackground();
	void loadWindowStartGameBackground();
	void loadWindowEndGameBackground();
	void loadWindowAboutBackground();
	void loadWindowScoresBackground();

	void startGamePage();
	void chooseLevelPage();
	void aboutPage();
	void scoresPage();
	void executeGame(int difficulty);
	void endGamePage(int score, int difficulty);

	void displaySnake(GameMap &game, int difficulty);
	void displayItem(int x, int y, char c);
	void displayGameDetails(GameMap &game, std::vector<Position*> pos);

	void printImage(char textureName, int x, int y, int angle);
	void printText(Texture textureName, int x, int y);
	void printTextScores(Texture textureName, int x, int y, int angle, int w, int h);

	void populateEasyLevelPlayers();
	void populateMediumLevelPlayers();
	void populateHardLevelPlayers();

	int tailDirection(GameMap &game);

	~Game();
	
};

