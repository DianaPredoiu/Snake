#pragma once

#include <string>
#include <vector>
#include "Snake.h"
#include "Player.h"
#include "Food.h"
#include "Bonus.h"
#include "Surprise.h"

class GameMap
{
private:
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


public:
	//Constructor
	GameMap();
	GameMap(int width, int height);
	// If there are better ways for the following two, please improve
	void gridAloc();
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
	// Accessor for the player
	//Player& getPlayer();
	// we don't required setters for the grid size as we pass it through the constructor
	// Setter for the player
	//void setPlayer(Player player);
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

	void addFood();
	void addBonus();
	void addSurprise();
	std::vector<Position*> initializeGrid(std::vector<Position*> oldPositions);
	friend std::ostream& operator<<(std::ostream& os, const GameMap& obj);

};