#include "MoveDown.h"

bool MoveDown::execute(GameMap& game)
{
	if (game.getSnake().getCoordinates().at(0)->getY() < game.getHeight() - 1)
	{
		if ((game.getSnake().getCoordinates().at(0)->getY() + 1) != game.getSnake().getCoordinates().at(1)->getY())
		{
			for (int i = game.getSnake().getCoordinates().size() - 1; i > 0; i--)
			{
				game.getSnake().getCoordinates().at(i)->setX(game.getSnake().getCoordinates().at(i - 1)->getX());
				game.getSnake().getCoordinates().at(i)->setY(game.getSnake().getCoordinates().at(i - 1)->getY());
			}

			game.getSnake().getCoordinates().at(0)->setY(game.getSnake().getCoordinates().at(0)->getY() + 1);
		}
	}
	else
		return true;

	return false;
}