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

	SDL_Surface* screenSurface;

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* background;

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


	std::map<char, SDL_Texture*> textures;

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


public:
	Game();

	bool init();
	void loadTextures();

	void loadWindowGameBackground();
	void loadWindowStartGameBackground();
	void loadWindowEndGameBackground();

	void startGamePage();
	void chooseLevelPage();
	void aboutPage();
	void executeGame(int difficulty);
	void endGamePage(int score);

	void displaySnake(GameMap &game, int difficulty);
	void displayItem(int x, int y, char c);
	void displayGameDetails(GameMap &game, std::vector<Position*> pos);

	void printImage(char textureName, int x, int y, int angle);
	void printText(Texture textureName, int x, int y, int angle, int w, int h);
	void printRectTextColored(Texture textureName, int x, int y, int angle, int w, int h);

	int tailDirection(GameMap &game);

	~Game();
	
};

