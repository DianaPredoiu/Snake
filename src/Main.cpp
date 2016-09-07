#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "GameMap.h"
#include "Rules.h"
#include "catch.hpp"
#include "DLLExportOptions.h"
#include "Main.h"

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

	while (true)
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
					rules.leftMove();
					displayGameDetails(game, positions);
					if (game.getSnake().getCoordinates().at(0)->getX() < 0 || rules.eatItself() == true)
					{
						std::cout << "GAME OVER!" << std::endl;
						break;
					}
					break;

				case VK_UP:
					rules.upMove();
					displayGameDetails(game, positions);
					if (game.getSnake().getCoordinates().at(0)->getY() < 0 || rules.eatItself() == true)
					{
						std::cout << "GAME OVER!" << std::endl;
						break;
					}
					break;

				case VK_RIGHT:
					rules.rightMove();
					displayGameDetails(game, positions);
					if (game.getSnake().getCoordinates().at(0)->getX() > game.getWidth() - 1 || rules.eatItself() == true)
					{
						std::cout << "GAME OVER!" << std::endl;
						break;
					}
					break;

				case VK_DOWN:
					rules.downMove();
					displayGameDetails(game, positions);
					if (game.getSnake().getCoordinates().at(0)->getY() > game.getHeight() - 1 || rules.eatItself() == true)
					{
						std::cout << "GAME OVER!" << std::endl;
						break;
					}
					break;
				}
			}

		}
		else
		{
			if (game.getSnake().getCoordinates().at(0)->getY() >= 0)
			{
				//if the body is left to the head => snake moves to right
				if (game.getSnake().getCoordinates().at(1)->getX() == (game.getSnake().getCoordinates().at(0)->getX() - 1))
				{
					if (rules.rightMove() == true || rules.eatItself() == true)
					{
						std::cout << std::endl << "GAME OVER!" << std::endl;
						break;
					}
				}

				//if the body is right to the head => snake moves to the left
				if (game.getSnake().getCoordinates().at(1)->getX() == (game.getSnake().getCoordinates().at(0)->getX() + 1))
				{
					if (rules.leftMove() == true || rules.eatItself() == true)
					{
						std::cout << std::endl << "GAME OVER!" << std::endl;
						break;
					}
				}

				//if the body is up to the head => snake moves down
				if (game.getSnake().getCoordinates().at(1)->getY() == (game.getSnake().getCoordinates().at(0)->getY() - 1))
				{
					if (rules.downMove() == true || rules.eatItself() == true)
					{
						std::cout << std::endl << "GAME OVER!" << std::endl;
						break;
					}
				}

				//if the body is down to the head => snake moves up
				if (game.getSnake().getCoordinates().at(1)->getY() == (game.getSnake().getCoordinates().at(0)->getY() + 1))
				{
					if (rules.upMove() == true || rules.eatItself() == true)
					{
						std::cout << std::endl << "GAME OVER!" << std::endl;
						break;
					}
				}


				displayGameDetails(game, positions);
				if (game.getSnake().getCoordinates().at(0)->getY() < 0 || rules.eatItself() == true)
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
