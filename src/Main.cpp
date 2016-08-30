#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "GameMap.h"
#include "catch.hpp"

//move these into rules class
void left(GameMap &game)
{
	//std::cout << "Left" << std::endl;  // key left
	//----mai trebuie adaugate conditii----

	if (game.getSnake().getCoordinates().at(0)->getX() != 0)
	{
		if ((game.getSnake().getCoordinates().at(0)->getX() - 1) != game.getSnake().getCoordinates().at(1)->getX())
		{
			for (int i = game.getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game.getSnake().getCoordinates().at(i)->setX(game.getSnake().getCoordinates().at(i - 1)->getX());
				game.getSnake().getCoordinates().at(i)->setY(game.getSnake().getCoordinates().at(i - 1)->getY());
			}
			game.getSnake().getCoordinates().at(0)->setX(game.getSnake().getCoordinates().at(0)->getX() - 1);

			system("cls");
			game.initializeGrid();
			std::cout << game;
			if (game.getSnake().getCoordinates().at(0)->getX() < 0)
				std::cout << "GAME OVER!" << std::endl;
		}
	}
	else
		std::cout << "GAME OVER!" << std::endl;
}

void up(GameMap &game)
{
	//std::cout << "Up" << std::endl;//key up
	//----mai trebuie adaugate conditii----
	if (game.getSnake().getCoordinates().at(0)->getY() != 0 )
	{
		if ((game.getSnake().getCoordinates().at(0)->getY() - 1) != game.getSnake().getCoordinates().at(1)->getY())
		{
			//tail
			game.getSnake().getCoordinates().at(game.getSnake().getCoordinates().size() - 1)->setY(game.getSnake().getCoordinates().at(game.getSnake().getCoordinates().size() - 2)->getY());
			game.getSnake().getCoordinates().at(game.getSnake().getCoordinates().size() - 1)->setX(game.getSnake().getCoordinates().at(game.getSnake().getCoordinates().size() - 2)->getX());

			//body
			for (int i = game.getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game.getSnake().getCoordinates().at(i)->setX(game.getSnake().getCoordinates().at(i - 1)->getX());
				game.getSnake().getCoordinates().at(i)->setY(game.getSnake().getCoordinates().at(i - 1)->getY());
			}

			//head
			game.getSnake().getCoordinates().at(0)->setY(game.getSnake().getCoordinates().at(0)->getY() - 1);

			system("cls");
			game.initializeGrid();
			std::cout << game;
			if (game.getSnake().getCoordinates().at(0)->getY() < 0)
				std::cout << "GAME OVER!" << std::endl;
		}
		
	}
	else
		std::cout << "GAME OVER!" << std::endl;
}

void right(GameMap &game)
{
	//std::cout << "Right" << std::endl;  // key right
	//----mai trebuie adaugate conditii----
	//gen daca head-ul e in stanga nu ar trebui sa faca dreapta dar face :))
	if (game.getSnake().getCoordinates().at(0)->getX() != game.getWidth() - 1)
	{
		if ((game.getSnake().getCoordinates().at(0)->getX() + 1) != game.getSnake().getCoordinates().at(1)->getX())
		{
			for (int i = game.getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game.getSnake().getCoordinates().at(i)->setX(game.getSnake().getCoordinates().at(i - 1)->getX());
				game.getSnake().getCoordinates().at(i)->setY(game.getSnake().getCoordinates().at(i - 1)->getY());
			}

			game.getSnake().getCoordinates().at(0)->setX(game.getSnake().getCoordinates().at(0)->getX() + 1);

			system("cls");
			game.initializeGrid();
			std::cout << game;
			if (game.getSnake().getCoordinates().at(0)->getX() == game.getWidth())
				std::cout << "GAME OVER!" << std::endl;
		}
		
	}
	else
		std::cout << "GAME OVER!" << std::endl;
}

void down(GameMap &game)
{
	//std::cout << "Down" << std::endl;   // key down
	//----mai trebuie adaugate conditii----
	if (game.getSnake().getCoordinates().at(0)->getY() != game.getHeight() - 1)
	{
		if ( (game.getSnake().getCoordinates().at(0)->getY() + 1 ) != game.getSnake().getCoordinates().at(1)->getY() )
		{
			for (int i = game.getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game.getSnake().getCoordinates().at(i)->setX(game.getSnake().getCoordinates().at(i - 1)->getX());
				game.getSnake().getCoordinates().at(i)->setY(game.getSnake().getCoordinates().at(i - 1)->getY());
			}

			game.getSnake().getCoordinates().at(0)->setY(game.getSnake().getCoordinates().at(0)->getY() + 1);

			system("cls");
			game.initializeGrid();
			std::cout << game;
			if (game.getSnake().getCoordinates().at(0)->getY() == game.getHeight())
				std::cout << "GAME OVER!" << std::endl;
		}
		
	}
	else
		std::cout << "GAME OVER!" << std::endl;
}

int main()
{
	GameMap game(10, 10);
	game.initializeGrid();
	std::cout << game;

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
					left(game);
					break;

				case VK_UP:
					up(game);
					break;

				case VK_RIGHT:
					right(game);

					break;

				case VK_DOWN:
					down(game);
					break;
				}
			}
			
		}
		else
		{
			if (game.getSnake().getCoordinates().at(0)->getY() != 0 )
			{
				//if the body is left to the head => snake moves to right
				if (game.getSnake().getCoordinates().at(1)->getX() == (game.getSnake().getCoordinates().at(0)->getX() - 1))
				{
					right(game);
				}

				//if the body is right to the head => snake moves to the left
				if (game.getSnake().getCoordinates().at(1)->getX() == (game.getSnake().getCoordinates().at(0)->getX() + 1))
				{
					left(game);
				}

				//if the body is up to the head => snake moves down
				if (game.getSnake().getCoordinates().at(1)->getY() == (game.getSnake().getCoordinates().at(0)->getY() - 1))
				{
					down(game);
				}

				//if the body is down to the head => snake moves up
				if (game.getSnake().getCoordinates().at(1)->getY() == (game.getSnake().getCoordinates().at(0)->getY() + 1))
				{
					up(game);
				}

				system("cls");
				Sleep(50);
				game.initializeGrid();
				std::cout << game;
				if (game.getSnake().getCoordinates().at(0)->getY() < 0)
					std::cout << "GAME OVER!" << std::endl;
			}
			else
				std::cout << "GAME OVER!" << std::endl;
		}



	}

	return 0;
}