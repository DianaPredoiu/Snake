#include "GameMap.h"

GameMap::GameMap() {}

void GameMap::gridAloc()
{
	grid = new char*[height];
	for (int i = 0; i < height; ++i)
		grid[i] = new char[width];


}

void GameMap::initializeGrid()
{
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			grid[i][j] = ' ';

	//write the head into the grid
	grid[snake.getCoordinates().at(0)->getY()][snake.getCoordinates().at(0)->getX()] = snake.getHeadSymbol();

	//body
	for (int i = 1; i < snake.getCoordinates().capacity() - 1;i++)
		grid[snake.getCoordinates().at(i)->getY()][snake.getCoordinates().at(i)->getX()] = snake.getBodySymbol(); 
	
	//tail
	grid[snake.getCoordinates().at(snake.getCoordinates().size() - 1)->getY()]
		[snake.getCoordinates().at(snake.getCoordinates().size() - 1)->getX()] = snake.getTailSymbol();

}

GameMap::GameMap(int width, int height)
{
	// set the instance variables
	this->snake = Snake();
	this->width = width;
	this->height = height;
	// allocate the memory for the grid
	gridAloc();
	
}

GameMap::~GameMap()
{
	for (int i = 0; i < width; ++i)
		delete grid[i];
	delete[] grid;
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

int GameMap:: getScore()
{ 
	return score; 
}

char GameMap::getGameGrid()
{
	return **grid;
}

//Player& GameMap:: getPlayer()
//{
//	return this->player;
//}

//void GameMap:: setPlayer(Player player)
//{
//	this->player = player;
//}

void GameMap:: setSnake(Snake snake)
{
	this->snake = snake;
}

void GameMap:: setScore(int requiredScore)
{
	score = requiredScore;
}



std::ostream & operator<<(std::ostream& out, const GameMap& map)
{
	
	for (int i = 0; i < map.width+ 2; i++)
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
