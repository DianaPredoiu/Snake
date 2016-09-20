#include <iostream>
#include "SDL.h"
#include <Game.h>
#include <Windows.h>
#include <Player.h>
#include "SQLite.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Game *game = new Game();
	game->startGamePage();

	SQLite sql;
	sql.insert(Player("ana", 2200));
	//sql.select();

	return 0;
}