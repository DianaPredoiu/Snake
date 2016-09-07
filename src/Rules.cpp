#include "Rules.h"
#include <iostream>

Rules::Rules(GameMap *game)
{
	this->game = game;
}

bool Rules::upMove()
{
	//std::cout << "Up" << std::endl;//key up
	//----mai trebuie adaugate conditii----
	if (game->getSnake().getCoordinates().at(0)->getY() > 0)
	{
		if ((game->getSnake().getCoordinates().at(0)->getY() - 1) != game->getSnake().getCoordinates().at(1)->getY())
		{
			//tail
			game->getSnake().getCoordinates().at(game->getSnake().getCoordinates().size() - 1)->setY(game->getSnake().getCoordinates().at(game->getSnake().getCoordinates().size() - 2)->getY());
			game->getSnake().getCoordinates().at(game->getSnake().getCoordinates().size() - 1)->setX(game->getSnake().getCoordinates().at(game->getSnake().getCoordinates().size() - 2)->getX());

			//body
			for (int i = game->getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game->getSnake().getCoordinates().at(i)->setX(game->getSnake().getCoordinates().at(i - 1)->getX());
				game->getSnake().getCoordinates().at(i)->setY(game->getSnake().getCoordinates().at(i - 1)->getY());
			}

			//head
			game->getSnake().getCoordinates().at(0)->setY(game->getSnake().getCoordinates().at(0)->getY() - 1);

			//system("cls");
			
		}

	}
	else
	{
		std::cout << "GAME OVER!" << std::endl;
		return true;
	}
	return false;
}

bool Rules::downMove()
{
	//std::cout << "Down" << std::endl;   // key down
	//----mai trebuie adaugate conditii----
	if (game->getSnake().getCoordinates().at(0)->getY() != game->getHeight() - 1)
	{
		if ((game->getSnake().getCoordinates().at(0)->getY() + 1) != game->getSnake().getCoordinates().at(1)->getY())
		{
			for (int i = game->getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game->getSnake().getCoordinates().at(i)->setX(game->getSnake().getCoordinates().at(i - 1)->getX());
				game->getSnake().getCoordinates().at(i)->setY(game->getSnake().getCoordinates().at(i - 1)->getY());
			}

			game->getSnake().getCoordinates().at(0)->setY(game->getSnake().getCoordinates().at(0)->getY() + 1);

			//system("cls");
			
		}

	}
	else
	{
		std::cout << "GAME OVER!" << std::endl;
		return true;
	}
	return false;
}

bool Rules::leftMove()
{
	//std::cout << "Left" << std::endl;  // key left
	//----mai trebuie adaugate conditii----

	if (game->getSnake().getCoordinates().at(0)->getX() != 0)
	{
		if ((game->getSnake().getCoordinates().at(0)->getX() - 1) != game->getSnake().getCoordinates().at(1)->getX())
		{
			for (int i = game->getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game->getSnake().getCoordinates().at(i)->setX(game->getSnake().getCoordinates().at(i - 1)->getX());
				game->getSnake().getCoordinates().at(i)->setY(game->getSnake().getCoordinates().at(i - 1)->getY());
			}
			game->getSnake().getCoordinates().at(0)->setX(game->getSnake().getCoordinates().at(0)->getX() - 1);

			//system("cls");
			
		}
	}
	else
	{
		std::cout << "GAME OVER!" << std::endl;
		return true;
	}
	return false;
}

bool Rules::rightMove()
{
	//std::cout << "Right" << std::endl;  // key right
	//----mai trebuie adaugate conditii----
	//gen daca head-ul e in stanga nu ar trebui sa faca dreapta dar face :))
	if (game->getSnake().getCoordinates().at(0)->getX() != game->getWidth() - 1)
	{
		if ((game->getSnake().getCoordinates().at(0)->getX() + 1) != game->getSnake().getCoordinates().at(1)->getX())
		{
			for (int i = game->getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game->getSnake().getCoordinates().at(i)->setX(game->getSnake().getCoordinates().at(i - 1)->getX());
				game->getSnake().getCoordinates().at(i)->setY(game->getSnake().getCoordinates().at(i - 1)->getY());
			}

			game->getSnake().getCoordinates().at(0)->setX(game->getSnake().getCoordinates().at(0)->getX() + 1);

			//system("cls");
			
		}

	}
	else
	{
		std::cout << "GAME OVER!" << std::endl;
		return true;
	}
	return false;
}

bool Rules::eatItself()
{
	/*for (std::vector<Position*>::iterator it = game->getSnake().getCoordinates().begin() + 1; it != game->getSnake().getCoordinates().end(); ++it)*/
	for (int i = 1; i < game->getSnake().getCoordinates().size(); i++)
	{
		/*if (game->getSnake().getCoordinates().at(0)->getX() == (*it)->getX() && game->getSnake().getCoordinates().at(0)->getY() == (*it)->getY())*/
		if (game->getSnake().getCoordinates().at(0)->getX() == game->getSnake().getCoordinates().at(i)->getX()
			&& game->getSnake().getCoordinates().at(0)->getY() == game->getSnake().getCoordinates().at(i)->getY())
			return true;
	}

	return false;
}
