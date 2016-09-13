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

class Game{

private:
	bool working;
	bool quit;
	bool onKeyPress;
	int score;
	int waitTime;//levels

	SDL_Surface* screenSurface;

	SDL_Window* window;
	SDL_Renderer* renderer;
	//SDL_Event event;
	TTF_Font* font;

	SDL_Color textColor;

	Texture wall;
	SDL_Texture* background;

	Texture head;
	Texture body;
	Texture tail;

	std::map<char, SDL_Texture*> textures;

	GameMap gMap;
	/*const waitTime = 1;*/

public:
	Game();

	bool init();
	void executeGame();

	void displayGameDetails(GameMap &game, std::vector<Position*> pos);
	void displaySnake();

	void loadImage(char textureName, int x, int y);

	bool hasTheGameStarted();

	void loadTextures();
	void loadWindowWithBackground();

	~Game();
	
};

