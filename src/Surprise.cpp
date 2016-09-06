#include "Surprise.h"
#include <random>

Surprise::Surprise()
{
	this->points = 20 + (std::rand() % 31);//make it random between 20-50 p
	this->symbol = '?';
	this->time = 7 + (std::rand() % 9);//seconds must be random too between 7-15
	this->effect = Effects(std::rand() % 3);
	this->coordinates.setX(1);
	this->coordinates.setY(1);
	this->state = false;
}

Surprise::Surprise(int points, char symbol, int time, Effects effect, Position coordinates)
{
	this->points = points;
	this->symbol = symbol;
	this->time = time;
	this->effect = effect;
	this->coordinates = coordinates;
	this->state = false;

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

Position Surprise::getCoordinates()
{
	return coordinates;
}

void Surprise::setCoordinates(Position coordinates)
{
	this->coordinates = coordinates;
}

bool Surprise::getState()
{
	return state;
}

void Surprise::setState(bool state)
{
	this->state = state;
}


Surprise::~Surprise()
{

}