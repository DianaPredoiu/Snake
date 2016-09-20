#include "GameMap.h"
#include <iostream>
#include <random>


#pragma region Constructors/Destructor
GameMap::GameMap()
{

}

GameMap::GameMap(int width, int height)
{
	// set the instance variables
	this->snake = Snake();
	this->food = Food();
	this->bonus = Bonus();
	this->surprise = Surprise();
	this->width = width;
	this->height = height;

	// allocate the memory for the grid
	grid = new char*[height];
	for (int i = 0; i < height; ++i)
		grid[i] = new char[width];

	countFood = 0;
	countBonus = 0;
}

GameMap::GameMap(const GameMap &map)
{
	std::cout << "copy";
}

GameMap::~GameMap()
{
	for (int i = 0; i < width; ++i)
		delete grid[i];
	delete[] grid;
}

#pragma endregion

#pragma region Add Items

bool GameMap::checkItemPosition(int x, int y)
{
	for (int i = 0; i < snake.getCoordinates().size(); i++)
		if (snake.getCoordinates().at(i)->getX() == x &&
			snake.getCoordinates().at(i)->getY() == y)
			return false;
	return true;
}

void GameMap::addFood()
{
	while (food.getState() == false)
	{
		food.setState(true);
		food.setCoordinates(Position(std::rand() % width, std::rand() % height));
		for (int i = 0; i < snake.getCoordinates().size(); i++)
			if (snake.getCoordinates().at(i)->getY() == food.getCoordinates().getY() && snake.getCoordinates().at(i)->getX() == food.getCoordinates().getX())
				food.setCoordinates(Position(std::rand() % width, std::rand() % height));
		if (checkItemPosition(food.getCoordinates().getX(), food.getCoordinates().getY()) == false)
			food.setState(false);
	}

}

void GameMap::addBonus()
{
	while (bonus.getState() == false)
	{
		bonus = Bonus();
		bonus.setState(true);
		bonus.setCoordinates(Position(std::rand() % width, std::rand() % height));
		if (bonus.getCoordinates().getX() == food.getCoordinates().getX() && bonus.getCoordinates().getY() == food.getCoordinates().getY())
			bonus.setCoordinates(Position(std::rand() % width, std::rand() % height));
		for (int i = 0; i < snake.getCoordinates().size(); i++)
			if (snake.getCoordinates().at(i)->getY() == bonus.getCoordinates().getY() && snake.getCoordinates().at(i)->getX() == bonus.getCoordinates().getX())
				bonus.setCoordinates(Position(std::rand() % width, std::rand() % height));
		if (checkItemPosition(bonus.getCoordinates().getX(), bonus.getCoordinates().getY()) == false)
			bonus.setState(false);
	}
}

void GameMap::addSurprise()
{
	while (surprise.getState() == false)
	{
		surprise = Surprise();
		surprise.setState(true);
		surprise.setCoordinates(Position(std::rand() % width, std::rand() % height));
		if (surprise.getCoordinates().getX() == food.getCoordinates().getX() && surprise.getCoordinates().getY() == food.getCoordinates().getY())
			surprise.setCoordinates(Position(std::rand() % width, std::rand() % height));
		if (surprise.getCoordinates().getX() == bonus.getCoordinates().getX() && surprise.getCoordinates().getY() == bonus.getCoordinates().getY())
			for (int i = 0; i < snake.getCoordinates().size(); i++)
				if (snake.getCoordinates().at(i)->getY() == surprise.getCoordinates().getY() && snake.getCoordinates().at(i)->getX() == surprise.getCoordinates().getX())
					surprise.setCoordinates(Position(std::rand() % width, std::rand() % height));
		if (checkItemPosition(surprise.getCoordinates().getX(), surprise.getCoordinates().getY()) == false)
			surprise.setState(false);
	}
}
#pragma endregion

#pragma region Manage Items
void GameMap::manageFood(std::vector<Position*> oldPositions)
{
	if (food.getState() == true)
	{
		grid[food.getCoordinates().getY()][food.getCoordinates().getX()] = food.getSymbol();
		if ((snake.getCoordinates().at(0)->getY() == food.getCoordinates().getY() && snake.getCoordinates().at(0)->getX() == food.getCoordinates().getX()))
		{
			food.setState(false);
			grid[food.getCoordinates().getY()][food.getCoordinates().getX()] = snake.getHeadSymbol();
			int size_ = oldPositions.size() - 1;
			Position* pos = new Position(oldPositions.at(size_)->getX(), oldPositions.at(size_)->getY());

			std::vector<Position*> positions = snake.getCoordinates();
			positions.push_back(pos);
			snake.setCoordinates(positions);
			score += food.getPoints();
			countFood++;
		}
	}
}

void GameMap::manageBonus(std::vector<Position*> oldPositions)
{
	if (countFood == 4)
	{
		addBonus();
		if (bonus.getState())
		{
			if (bonus.getTime() > 0)
			{
				grid[bonus.getCoordinates().getY()][bonus.getCoordinates().getX()] = bonus.getSymbol();
				bonus.setTime(bonus.getTime() - 1);
				if ((snake.getCoordinates().at(0)->getY() == bonus.getCoordinates().getY() && snake.getCoordinates().at(0)->getX() == bonus.getCoordinates().getX()))
				{
					bonus.setState(false);
					countFood = 0;
					score += bonus.getPoints();
					countBonus++;
					bonus.setTime(0);
				}
			}
			else
			{
				bonus.setState(false);
				countFood = 0;
				bonus.setTime(0);
			}

		}
	}
}

void GameMap::manageSurprise(std::vector<Position*> oldPositions)
{
	if (countBonus == 2)
	{
		addSurprise();
		if (surprise.getState())
		{
			if (surprise.getTime() > 0)
			{
				grid[surprise.getCoordinates().getY()][surprise.getCoordinates().getX()] = surprise.getSymbol();
				surprise.setTime(surprise.getTime() - 1);
				if ((snake.getCoordinates().at(0)->getY() == surprise.getCoordinates().getY() && snake.getCoordinates().at(0)->getX() == surprise.getCoordinates().getX()))
				{
					surprise.setState(false);
					countBonus = 0;
					switch (surprise.getEffect())
					{
					case SubstractPoints:
					{
						score -= surprise.getPoints();
						surprise.setTime(0);
						break;
					}

					case BonusEffect:
					{
						score += surprise.getPoints();
						surprise.setTime(0);
						break;
					}

					case HalveBody:
					{
						if (snake.getCoordinates().size() >= 6)
						{
							int length = snake.getCoordinates().size() / 2;
							std::vector<Position*> positions = snake.getCoordinates();
							positions.erase(positions.begin() + length, positions.end());
							snake.setCoordinates(positions);
							surprise.setTime(0);
						}
						break;
					}

					case NoEffect:
					{
						surprise.setTime(0);
						break;
					}
					}
				}
			}
			else
			{
				surprise.setState(false);
				surprise.setTime(0);
				countBonus = 0;
			}
		}
	}
}
#pragma endregion

std::vector<Position*>  GameMap::initializeGrid(std::vector<Position*> oldPositions)
{
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			grid[i][j] = ' ';

	//write the head into the grid
	grid[snake.getCoordinates().at(0)->getY()][snake.getCoordinates().at(0)->getX()] = snake.getHeadSymbol();

	//body
	for (int i = 1; i < snake.getCoordinates().capacity() - 1; i++)
		grid[snake.getCoordinates().at(i)->getY()][snake.getCoordinates().at(i)->getX()] = snake.getBodySymbol();

	//tail
	grid[snake.getCoordinates().at(snake.getCoordinates().size() - 1)->getY()]
		[snake.getCoordinates().at(snake.getCoordinates().size() - 1)->getX()] = snake.getTailSymbol();

	//addFood 
	if (countFood == 4)
	{
		//addBonus
		manageBonus(oldPositions);
	}
	else if (countBonus == 2)
	{
		//addSurprise
		manageSurprise(oldPositions);
	}
	else
	{
		addFood();
		manageFood(oldPositions);
	}
	

	return snake.getCoordinates();

}

#pragma region Get/Set

int GameMap::getCountFood()
{
	return countFood;
}

void GameMap::setCountFood(int count)
{
	countFood = count;
}

Snake GameMap::getSnake()
{
	return snake;
}

int GameMap::getWidth() const
{
	return width;
}

int GameMap::getHeight() const
{
	return height;
}

int GameMap::getScore()
{
	return score;
}

char GameMap::getGameGrid()
{
	return **grid;
}

void GameMap::setSnake(Snake snake)
{
	this->snake = snake;
}

void GameMap::setScore(int requiredScore)
{
	score = requiredScore;
}

Food GameMap::getFood()
{
	return food;
}

Bonus GameMap::getBonus()
{
	return bonus;
}

Surprise GameMap::getSurprise()
{
	return surprise;
}

#pragma endregion

#pragma region Operators

std::ostream & operator<<(std::ostream& out, const GameMap& map)
{

	for (int i = 0; i < map.width + 2; i++)
		out << "-";
	out << std::endl;
	for (int i = 0; i < map.height; i++)
	{
		out << "|";
		for (int j = 0; j < map.width; j++)
		{
			out << map.grid[i][j];
		}
		out << "|" << std::endl;
	}
	for (int i = 0; i < map.width + 2; i++)
		out << "-";
	return out;

}

#pragma endregion