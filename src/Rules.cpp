#include "Rules.h"
#include <iostream>

#pragma region Constructor
Rules::Rules(GameMap *game)
{
	this->game = game;
}
#pragma endregion 

#pragma region Moves 
bool Rules::upMove()
{
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
		}
	}
	else
		return true;

	return false;
}

bool Rules::downMove()
{
	if (game->getSnake().getCoordinates().at(0)->getY() < game->getHeight() - 1)
	{
		if ((game->getSnake().getCoordinates().at(0)->getY() + 1) != game->getSnake().getCoordinates().at(1)->getY())
		{
			for (int i = game->getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game->getSnake().getCoordinates().at(i)->setX(game->getSnake().getCoordinates().at(i - 1)->getX());
				game->getSnake().getCoordinates().at(i)->setY(game->getSnake().getCoordinates().at(i - 1)->getY());
			}

			game->getSnake().getCoordinates().at(0)->setY(game->getSnake().getCoordinates().at(0)->getY() + 1);	
		}
	}
	else
		return true;

	return false;
}

bool Rules::leftMove()
{
	if (game->getSnake().getCoordinates().at(0)->getX() > 0)
	{
		if ((game->getSnake().getCoordinates().at(0)->getX() - 1) != game->getSnake().getCoordinates().at(1)->getX())
		{
			for (int i = game->getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game->getSnake().getCoordinates().at(i)->setX(game->getSnake().getCoordinates().at(i - 1)->getX());
				game->getSnake().getCoordinates().at(i)->setY(game->getSnake().getCoordinates().at(i - 1)->getY());
			}
			game->getSnake().getCoordinates().at(0)->setX(game->getSnake().getCoordinates().at(0)->getX() - 1);
		}
	}
	else
		return true;

	return false;
}

bool Rules::rightMove()
{
	if (game->getSnake().getCoordinates().at(0)->getX() < game->getWidth() - 1)
	{
		if ((game->getSnake().getCoordinates().at(0)->getX() + 1) != game->getSnake().getCoordinates().at(1)->getX())
		{
			for (int i = game->getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game->getSnake().getCoordinates().at(i)->setX(game->getSnake().getCoordinates().at(i - 1)->getX());
				game->getSnake().getCoordinates().at(i)->setY(game->getSnake().getCoordinates().at(i - 1)->getY());
			}

			game->getSnake().getCoordinates().at(0)->setX(game->getSnake().getCoordinates().at(0)->getX() + 1);	
		}
	}
	else
		return true;

	return false;
}
#pragma endregion 

#pragma region Other rules

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

bool Rules::isOutOfBounds()
{
	if (eatItself())
		return true;

	//left
	if (game->getSnake().getCoordinates().at(0)->getX() < 0)
		return true;

	//up
	if (game->getSnake().getCoordinates().at(0)->getY() < 0)
		return true;

	//right
	if (game->getSnake().getCoordinates().at(0)->getX() > game->getWidth() - 1)
		return true;

	//down
	if (game->getSnake().getCoordinates().at(0)->getY() > game->getHeight() - 1)
		return true;

	return false;
}

bool Rules::continuousMovement()
{
	//std::cout << game->getSnake().getCoordinates().at(0)->getX() << "   " << game->getSnake().getCoordinates().at(0)->getY() << std::endl;
	
	if (game->getSnake().getCoordinates().at(0)->getY() >= 0)
	{
		//body left->head => snake moves to right
		if (game->getSnake().getCoordinates().at(1)->getX() == (game->getSnake().getCoordinates().at(0)->getX() - 1))
		{
			if (rightMove() == true)
				return true;
		}

		//body right->head => snake moves to the left
		if (game->getSnake().getCoordinates().at(1)->getX() == (game->getSnake().getCoordinates().at(0)->getX() + 1))
		{
			if (leftMove() == true)
				return true;
		}

		//body up->head => snake moves down
		if (game->getSnake().getCoordinates().at(1)->getY() == (game->getSnake().getCoordinates().at(0)->getY() - 1))
		{
			if (downMove() == true)
				return true;
		}

		//body down->head => snake moves up
		if (game->getSnake().getCoordinates().at(1)->getY() == (game->getSnake().getCoordinates().at(0)->getY() + 1))
		{
			if (upMove() == true)
				return true;
		}

		if (eatItself())
			return true;

	}
	else
		return true;
	return false;
}

#pragma endregion 

Rules::~Rules()
{

}