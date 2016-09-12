#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "GameMap.h"
#include "Rules.h"
#include "catch.hpp"
#include "DLLExportOptions.h"
#include "Main.h"
#include "Directions.h"
#include "SDL.h"


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

void Game()
{
	//GameMap game(15, 15);
	//Rules rules(&game);
	//
	//std::cout << game;
	//std::vector<Position*> positions = game.initializeGrid(game.getSnake().getCoordinates());

	//game.setScore(0);

	//
	////Event handler
	//SDL_Event e;

	//bool working = true;
	////While application is running
	//while (working)
	//{
	//	//Handle events on queue
	//	while (SDL_PollEvent(&e) != 0)
	//	{
	//		//User requests quit
	//		if (e.type == SDL_QUIT || e.type == SDLK_ESCAPE)
	//		{
	//			working = false;
	//		}
	//		//User presses a key
	//		else if (e.type == SDL_KEYDOWN)
	//		{
	//			//Select movements based on key press
	//			switch (e.key.keysym.sym)
	//			{
	//				std::cout << e.key.keysym.sym << std::endl;
	//			case SDLK_UP:
	//				working = (!rules.upMove());
	//				break;

	//			case SDLK_DOWN:
	//				working = (!rules.downMove());
	//				break;

	//			case SDLK_LEFT:
	//				working = (!rules.leftMove());
	//				break;

	//			case SDLK_RIGHT:
	//				working = (!rules.rightMove());
	//				break;

	//			default:
	//				break;
	//			}
	//		}
	//		displayGameDetails(game, positions);
	//		if (rules.isOutOfBounds() || working == false)
	//		{
	//			std::cout << "GAME OVER" << std::endl;
	//			working = false;
	//		}
	//	}

	//		if (!rules.continuousMovement())
	//		{
	//			displayGameDetails(game, positions);
	//			if (rules.isOutOfBounds())
	//			{
	//				std::cout << std::endl << "GAME OVER!" << std::endl;
	//				break;
	//			}
	//		}
	//		else
	//		{
	//			std::cout << std::endl << "GAME OVER!" << std::endl;
	//			break;
	//		}
	//	
	//}

}
