#include <iostream>
#include "Main.h"
#include "SDL.h"
#include <Game.h>

void displayGameDetails(GameMap &game, std::vector<Position*> pos)
{
	Sleep(300);
	system("cls");

	game.initializeGrid(pos);
	std::cout << game;
	std::cout << std::endl << std::endl << "---Score: " << game.getScore() << "  ---" << std::endl << std::endl;

	if (game.getBonus().getState() == true)
		std::cout << "---Bonus Time: " << game.getBonus().getTime() << "  ---" << std::endl << std::endl;

	if (game.getSurprise().getState() == true)
	{
		std::cout << "---Surprise Time: " << game.getSurprise().getTime() << "  ---" << std::endl << std::endl;
		std::cout << std::endl << "---Effect: " << game.getSurprise().getEffect() << "  ---";
	}
}


int main(int argc, char* argv[])
{
<<<<<<< HEAD
	Game *game = new Game();
	game->executeGame();
	
=======
	

>>>>>>> origin/master
	return 0;
}