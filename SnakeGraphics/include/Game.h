#pragma once
#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GameMap.h>
#include <Snake.h>
#include <Texture.h>

class Game{

private:
	bool working;
	bool quit;
	bool onKeyPress;
	int score;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	TTF_Font* font;

	SDL_Color textColor;

	Texture wall;
	Texture textureBackground;
	Texture textureHead;
	Texture textureBody;
	Texture textureTail;

	GameMap gMap;

public:
	Game();
	~Game();
	int waitTime;
	void executeGame();
	bool hasTheGameStarted();
	void render();
	void GameLogic();
	void updateMove();
	void checkCollision();
	
};

