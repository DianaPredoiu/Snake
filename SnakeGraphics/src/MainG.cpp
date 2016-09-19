#include <iostream>
#include "SDL.h"
#include <Game.h>
#include <Windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Game *game = new Game();
	game->startGamePage();

	return 0;
}