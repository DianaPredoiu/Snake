#include "Food.h"

Food::Food()
{
	this->points = 10;
	this->symbol = 'F';
}

Food::Food(int points, char symbol)
{
	this->points = points;
	this->symbol = symbol;
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
