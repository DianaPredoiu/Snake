#pragma once

#include <string>
#include <vector>
#include "Snake.h"

class GameMap 
{
private:
	Snake snake;
	int width, height;
	char **grid;
	int score;
	//Player player;

public:
	//Constructor
	GameMap();
	GameMap(int width, int height);

	// If there are better ways for the following two, please improve
	void gridAloc();

	void GameMap::initializeGrid();

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

	~GameMap();

	friend std::ostream& operator<<(std::ostream& os, const GameMap& obj);

};

