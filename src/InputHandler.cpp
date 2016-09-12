#include "InputHandler.h"

InputHandler::InputHandler()
{
	moveDown = new MoveDown();
	moveUp = new MoveUp();
	moveLeft = new MoveLeft();
	moveRight = new MoveRight();

	commands[SDLK_UP] = moveUp;
	commands[SDLK_RIGHT] = moveRight;
	commands[SDLK_DOWN] = moveDown;
	commands[SDLK_LEFT] = moveLeft;

	commands[SDLK_w] = moveUp;
	commands[SDLK_d] = moveRight;
	commands[SDLK_s] = moveDown;
	commands[SDLK_a] = moveLeft;
}

void InputHandler::addCommand(int key, Command *command)
{
	commands[key] = command;
}

std::map<int, Command*> InputHandler::getCommands()
{
	return commands;
}

bool InputHandler::keyDown(SDL_Event event, GameMap& game)
{
	if (event.type == SDL_QUIT || event.type == SDLK_ESCAPE)
		return false;
	else if (event.type == SDL_KEYDOWN)
	{
		std::map<int, Command*>::iterator it = commands.find(event.key.keysym.sym);
		if (it != commands.end())
			return (!commands[event.key.keysym.sym]->execute(game));
	}
		
	return true;
}

InputHandler::~InputHandler()
{
	delete moveDown;
	delete moveLeft;
	delete moveRight;
	delete moveUp;
}