#include "Food.h"

Food::Food()
{
	this->points = 10;
	this->symbol = 'F';
	this->coordinates.setX(1);
	this->coordinates.setY(1);
	this->state = false;
}

Food::Food(int points, char symbol, Position coordinates)
{
	this->points = points;
	this->symbol = symbol;
	this->coordinates = coordinates;
	this->state = false;
}

int Food::getPoints()
{
	return points;
}

void Food::setPoints(int points)
{
	this->points = points;
}

char Food::getSymbol()
{
	return symbol;
}

void Food::setSymbol(char symbol)
{
	this->symbol = symbol;
}

Position Food::getCoordinates()
{
	return coordinates;
}

void Food::setCoordinates(Position coordinates)
{
	this->coordinates = coordinates;
}

bool Food::getState()
{
	return state;
}

void Food::setState(bool state)
{
	this->state = state;
}

Food::~Food()
{

}