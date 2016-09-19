#pragma once
#include "SDL.h"
#include <iostream>

enum ButtonActions
{
	newGame,
	loadGame,
	replayGame,
	quitGame
};

class Button
{
	SDL_Rect box;
	std::string text;
	ButtonActions action;

public:
	Button(ButtonActions action, int x, int y, int width, int height);

	SDL_Rect getBox();

	bool isPressed(SDL_Event e);

	~Button();
};