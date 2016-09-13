#pragma once
#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GameMap.h>
#include <Snake.h>
#include <Texture.h>
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
	Texture background;

	std::map<std::string, Texture> textures;

	GameMap gMap;
	/*const waitTime = 1;*/

public:
	Game();
	~Game();

	bool init();
	
	void executeGame();
	bool hasTheGameStarted();
	void render();
	void gameLogic();
	void updateMove();
	void checkCollision();
	
};

