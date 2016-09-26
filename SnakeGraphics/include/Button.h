#pragma once
#include "SDL.h"
#include <iostream>

enum ButtonActions
{
	newGame,
	about,
	easy,
	medium,
	hard,
	addScore,
	back,
	viewScores,
	sound
};

class Button
{
	SDL_Rect box;
	std::string text;
	ButtonActions action;

public:
	Button(ButtonActions action, int x, int y, int width, int height);

	SDL_Rect getBox();

	void setCoordinates(int x ,int y);

	bool isPressed(SDL_Event e);

	~Button();
};