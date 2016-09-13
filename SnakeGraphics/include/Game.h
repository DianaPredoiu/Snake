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

	std::map<std::string, Texture> textures;

	GameMap gMap;
	/*const waitTime = 1;*/

public:
	Game();

	bool init();
	void executeGame();
	bool hasTheGameStarted();
	void render();
	void gameLogic();
	void updateMove();
	void checkCollision();
	void loadTextures();
	void loadWindowWithBackground();

	~Game();
	
};

