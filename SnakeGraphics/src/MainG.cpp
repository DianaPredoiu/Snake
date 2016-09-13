#include <iostream>
#include "Main.h"
#include "SDL.h"
#include <Game.h>


int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->executeGame();

	return 0;
}