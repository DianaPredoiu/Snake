#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "GameMap.h"
#include "Rules.h"
#include "catch.hpp"
#include "DLLExportOptions.h"
#include "Main.h"
#include "Directions.h"

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
	GameMap game(15, 15);
	Rules rules(&game);
	
	std::cout << game;
	std::vector<Position*> positions = game.initializeGrid(game.getSnake().getCoordinates());

	game.setScore(0);

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);// handle for the event
	DWORD NumInputs = 0;//number of inputs
	DWORD InputsRead = 0;//the input keyboard read
	INPUT_RECORD irInput;

	

	bool working = true;
	while (working)
	{
		GetNumberOfConsoleInputEvents(hInput, &NumInputs);

		if (NumInputs != 0)
		{
			ReadConsoleInput(hInput, &irInput, 1, &InputsRead);

			if (irInput.Event.KeyEvent.bKeyDown)
			{
				switch (irInput.Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_LEFT:
					working = (!rules.leftMove());
					break;

				case VK_UP:
					working = (!rules.upMove());
					break;

				case VK_RIGHT:
					working = (!rules.rightMove());
					break;

				case VK_DOWN:
					working = (!rules.downMove());
					break;
				}
				displayGameDetails(game, positions);
				if (rules.isOutOfBounds() || working == false)
				{
					std::cout << "GAME OVER" << std::endl;
					working = false;
				}
			}

		}
		else
		{
			if (!rules.continuousMovement())
			{
				displayGameDetails(game, positions);
				if (rules.isOutOfBounds())
				{
					std::cout << std::endl << "GAME OVER!" << std::endl;
					break;
				}
			}
			else
			{
				std::cout << std::endl << "GAME OVER!" << std::endl;
				break;
			}			
		}
	}

}
