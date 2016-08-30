#include "Bonus.h"
#include <random>

Bonus::Bonus()
{
	this->points = 15 + (std::rand() % 16);//make it random between 15-30 p
	this->symbol = 'B';
	this->time = 7 + (std::rand() % 9);//seconds must be random too between 7-15
}

Bonus::Bonus(int points, char symbol, int time)
{
	this->points = points;
	this->symbol = symbol;
	this->time = time;
}

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

Bonus::~Bonus()
{

}