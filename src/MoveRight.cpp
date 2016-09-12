#include "MoveRight.h"

bool MoveRight::execute(GameMap& game)
{
	if (game.getSnake().getCoordinates().at(0)->getX() < game.getWidth() - 1)
	{
		if ((game.getSnake().getCoordinates().at(0)->getX() + 1) != game.getSnake().getCoordinates().at(1)->getX())
		{
			for (int i = game.getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game.getSnake().getCoordinates().at(i)->setX(game.getSnake().getCoordinates().at(i - 1)->getX());
				game.getSnake().getCoordinates().at(i)->setY(game.getSnake().getCoordinates().at(i - 1)->getY());
			}

			game.getSnake().getCoordinates().at(0)->setX(game.getSnake().getCoordinates().at(0)->getX() + 1);
		}
	}
	else
		return true;

	return false;
}

