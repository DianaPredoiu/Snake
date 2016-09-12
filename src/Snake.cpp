#include "Snake.h"

#pragma region Constructors
Snake::Snake()
{
	this->coordinates.push_back(new Position(3, 1)); //head position
	this->coordinates.push_back(new Position(2, 1)); //body position
	this->coordinates.push_back(new Position(1, 1)); //tail position
	this->headSymbol = 'H';
	this->bodySymbol = 'b';
	this->tailSymbol = 'T';
}

Snake::Snake(int i, int j)
{
	this->coordinates.push_back(new Position(j, i)); //head position
	this->coordinates.push_back(new Position(j - 1, i)); //body position
	this->coordinates.push_back(new Position(j - 2, i)); //tail position
	this->headSymbol = 'H';
	this->bodySymbol = 'b';
	this->tailSymbol = 'T';
}
#pragma endregion 

#pragma region Get/Set
std::vector<Position*> Snake::getCoordinates() const
{
	return this->coordinates;
}

void Snake::setCoordinates(std::vector<Position*>  coordinates)
{
	this->coordinates = coordinates;
}

char Snake::getHeadSymbol()
{
	return this->headSymbol;
}

char Snake::getBodySymbol()
{
	return this->bodySymbol;
}

char Snake::getTailSymbol()
{
	return this->tailSymbol;
}
#pragma endregion 

#pragma region Destructor
Snake::~Snake()
{

}
#pragma endregion 