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

	SDL_Rect scoreRectangle;
	SDL_Rect bonusRectangle;
	SDL_Rect surpriseRectangle;

	Texture scoreTexture;
	Texture bonusTexture;
	Texture surpriseTexture;

	std::map<char, SDL_Texture*> textures;

	InputHandler *inputHandler;

	SDL_Rect textRectangle;
	Texture textTexture;
	SDL_Color textColor;
	SDL_Color bgColor;


public:
	Game();

	bool init();
	void loadTextures();
	void loadWindowWithBackground();

	void executeGame();

	void displaySnake(GameMap &game);
	void displayFood(int x, int y);
	void displayBonus(int x, int y);
	void displaySurprise(int x, int y);
	void displayGameDetails(GameMap &game, std::vector<Position*> pos);

	void printImage(char textureName, int x, int y, int angle);

	void printScores(Texture textureName, int x, int y, int angle);

	void printScore(std::string message, int x, int y, int angle);

	bool hasTheGameStarted();

	int tailDirection(GameMap &game);

	~Game();
	
};

