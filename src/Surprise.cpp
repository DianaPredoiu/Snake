#include "Surprise.h"
#include <random>

Surprise::Surprise()
{
	this->points = 20 + (std::rand() % 31);//make it random between 20-50 p
	this->symbol = 'S';
	this->time = 7 + (std::rand() % 9);//seconds must be random too between 7-15
	this->effect = Effects(std::rand() % 3);
}

Surprise::Surprise(int points, char symbol, int time, Effects effect)
{
	this->points = points;
	this->symbol = symbol;
	this->time = time;
	this->effect = effect;
}

int Surprise::getPoints()
{
	return points;
}

void Surprise::setPoints(int points)
{
	this->points = points;
}

char Surprise::getSymbol()
{
	return symbol;
}

void Surprise::setSymbol(char symbol)
{
	this->symbol = symbol;
}

int Surprise::getTime()
{
	return time;
}

void Surprise::setTime(int time)
{
	this->time = time;
}

Effects Surprise::getEffect()
{
	return effect;
}

void Surprise::setEffect(Effects effect)
{
	this->effect = effect;
}

Surprise::~Surprise()
{

}