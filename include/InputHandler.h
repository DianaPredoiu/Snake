#pragma once
#include <map>
#include "MoveDown.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include "MoveUp.h"
#include "SDL.h"
#include "DLLExportOptions.h"


class DLL_SNAKE  InputHandler
{
	Command *moveDown;
	Command *moveLeft;
	Command *moveRight;
	Command *moveUp;

	std::map<int, Command*> commands;

public:
	InputHandler();

	void addCommand(int key, Command *command);

	std::map<int, Command*> getCommands();

	bool keyDown(SDL_Event event, GameMap& game);

	~InputHandler();

};