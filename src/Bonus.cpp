#include "Bonus.h"
#include <random>

#pragma region Constructors
Bonus::Bonus()
{
	this->points = 15 + (std::rand() % 16);//make it random between 15-30 p
	this->symbol = 'B';
	this->time = 20 + (std::rand() % 11);//seconds must be random too between 10-20
	this->coordinates.setX(1);
	this->coordinates.setY(1);
	this->state = false;
}

Bonus::Bonus(int points, char symbol, int time, Position coordinates)
{
	this->points = points;
	this->symbol = symbol;
	this->time = time;
	this->coordinates = coordinates;
	this->state = false;
}
#pragma endregion

#pragma region Get/Set
int Bonus::getPoints()
{
	return points;
}

void Bonus::setPoints(int points)
{
	this->points = points;
}

char Bonus::getSymbol()
{
	return symbol;
}

void Bonus::setSymbol(char symbol)
{
	this->symbol = symbol;
}

int Bonus::getTime()
{
	return time;
}

void Bonus::setTime(int time)
{
	this->time = time;
}

Position Bonus::getCoordinates()
{
	return coordinates;
}

void Bonus::setCoordinates(Position coordinates)
{
	this->coordinates = coordinates;
}

bool Bonus::getState()
{
	return state;
}

void Bonus::setState(bool state)
{
	this->state = state;
}
#pragma endregion

#pragma region Destructor
Bonus::~Bonus()
{

}
#pragma endregion