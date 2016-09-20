#pragma once

#include <string>
#include <vector>
#include "Snake.h"
#include "Player.h"
#include "Food.h"
#include "Bonus.h"
#include "Surprise.h"
#include "DLLExportOptions.h"

class DLL_SNAKE GameMap
{
private:

#pragma region Fields
	Snake snake;

	int width, height;
	char **grid;

	int score;
	int countFood;
	int countBonus;

	Player player;

	Food food;
	Bonus bonus;
	Surprise surprise;
#pragma endregion

public:
	//Constructors, destructors
	GameMap();
	GameMap(const GameMap &map);
	GameMap(int width, int height);
	~GameMap();

	// Accessor for the snake
	Snake getSnake();

	// Accessor for the width
	int getWidth() const;

	// Accessor for the height
	int getHeight() const;

	// Accessor for the score
	int getScore();

	// Accessor for the grid
	char getGameGrid();

	// Setter for the snake
	void setSnake(Snake snake);

	// Setter for the score
	void setScore(int requiredScore);

	//get and set for countFood
	int getCountFood();
	void setCountFood(int count);

	Food getFood();
	Bonus getBonus();
	Surprise getSurprise();

	bool checkItemPosition(int x, int y);
	void addFood();
	void addBonus();
	void addSurprise();

	void manageFood(std::vector<Position*> oldPositions);
	void manageBonus(std::vector<Position*> oldPositions);
	void manageSurprise(std::vector<Position*> oldPositions);

	std::vector<Position*> initializeGrid(std::vector<Position*> oldPositions);

	friend DLL_SNAKE std::ostream& operator<<(std::ostream& os, const GameMap& obj);
};